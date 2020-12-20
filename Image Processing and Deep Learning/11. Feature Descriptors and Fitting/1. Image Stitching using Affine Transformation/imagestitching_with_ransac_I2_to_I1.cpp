
#include <opencv2\opencv.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\nonfree\nonfree.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#define RATIO_THR 0.4

using namespace std;
using namespace cv;

double euclidDistance(Mat& vec1, Mat& vec2);
int nearestNeighbor(Mat& vec, vector<KeyPoint>& keypoints, Mat& descriptors);
void findPairs(vector<KeyPoint>& keypoints1, Mat& descriptors1,
	vector<KeyPoint>& keypoints2, Mat& descriptors2,
	vector<Point2f>& srcPoints, vector<Point2f>& dstPoints, bool crossCheck, bool ratio_threshold);
int ratio_thresholding(Mat& vec, vector<KeyPoint>& keypoints, Mat& descriptors);
Mat cal_affine(vector<Point2f>& srcPoints, vector<Point2f>& dstPoints, int number_of_points);
void blend_stitching(const Mat I1, const Mat I2, Mat& I_f, int diff_x, int diff_y, float alpha);
int repeat_RANSAC(vector<Point2f>& srcPoints, vector<Point2f>& dstPoints, vector<Point2f>& ransac_src, vector<Point2f>& ransac_dst, Mat& A12);
Mat final_RANSAC(vector<Point2f>& srcPoints, vector<Point2f>& dstPoints, int number_of_points);

int main() {

	Mat input1 = imread("C:\\input1.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input2 = imread("C:\\input2.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input1_gray, input2_gray;

	if (!input1.data || !input2.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	cvtColor(input1, input1_gray, CV_RGB2GRAY);
	cvtColor(input2, input2_gray, CV_RGB2GRAY);
	input1.convertTo(input1, CV_32FC3, 1.0 / 255);
	input2.convertTo(input2, CV_32FC3, 1.0 / 255);

	// 1. FEATURE MATCHING 1) RUN SIFT DESCRIPTOR FOR TWO IMAGES
	FeatureDetector* detector = new SiftFeatureDetector(
		0,      // nFeatures
		4,      // nOctaveLayers
		0.04,   // contrastThreshold
		10,      // edgeThreshold
		1.6      // sigma
	);

	DescriptorExtractor* extractor = new SiftDescriptorExtractor();

	Size size = input2.size();
	Size sz = Size(size.width + input1_gray.size().width, max(size.height, input1_gray.size().height));
	Mat matchingImage = Mat::zeros(sz, CV_8UC3);


	vector<KeyPoint> keypoints1;
	Mat descriptors1;

	detector->detect(input1_gray, keypoints1);
	extractor->compute(input1_gray, keypoints1, descriptors1);
	printf("input1 : %d keypoints are found.\n", (int)keypoints1.size());

	vector<KeyPoint> keypoints2;
	Mat descriptors2;

	detector->detect(input2_gray, keypoints2);
	extractor->compute(input2_gray, keypoints2, descriptors2);

	printf("input2 : %zd keypoints are found.\n", keypoints2.size());
	printf("input1 : %zd keypoints %d %d descriptors.\n", keypoints1.size(), descriptors1.size().height, descriptors1.size().width);
	printf("input2 : %zd keypoints %d %d descriptors.\n", keypoints2.size(), descriptors2.size().height, descriptors2.size().width);

	// 1. FEATURE MATCHING 2) PERFORM THE FEATURE MATCHING USING NN, 3) USE BOTH CROSS-CHECKING AND RATIO-BASED THRESHOLDING
	vector<Point2f> srcPoints;
	vector<Point2f> dstPoints;
	bool crossCheck = true;
	bool ratio_threshold = true;
	//findPairs(keypoints1, descriptors1, keypoints2, descriptors2, srcPoints, dstPoints, crossCheck, ratio_threshold);
	findPairs(keypoints2, descriptors2, keypoints1, descriptors1, srcPoints, dstPoints, crossCheck, ratio_threshold);
	printf("%zd keypoints are matched.\n", srcPoints.size());

	int max_inlier_index = 0;
	vector <Point2f> max_inlier_ransac_src;
	vector <Point2f> max_inlier_ransac_dst;

	//set k=3 and proportion of outliers= 40% SO THE NUMBER OF TRIALS = 19
	for (int l = 0; l < 19; l++) {
		//AFFINE TRANSFORMATION ESTIMATION #1-2
		Mat A12 = cal_affine(srcPoints, dstPoints, srcPoints.size());
		Mat A21 = cal_affine(dstPoints, srcPoints, dstPoints.size());

		// AFFINE TRANSFORMATION ESTIMATION #3: Score by computing the number of inliers satisfying
		vector<Point2f> ransac_src;
		vector<Point2f> ransac_dst;
		int a = repeat_RANSAC(srcPoints, dstPoints, ransac_src, ransac_dst, A12);

		// AFFINE TRANSFORMATION ESTIMATION #4: Select the best affine tranformation + get T's inlier
		if (a > max_inlier_index) {
			printf("In %d try, MAX_INLINER_INDEX CHANGED. THE INDEX IS %d\n", l, a);
			max_inlier_index = a;
			max_inlier_ransac_src = ransac_src;
			max_inlier_ransac_dst = ransac_dst;
		}
	}

	printf("CHECK RANSAC COMPLETED\n");

	//AFFINE TRANSFORMATION ESTIMATION #5: Re-estimate the affine transformation
	Mat A12 = final_RANSAC(max_inlier_ransac_src, max_inlier_ransac_dst, max_inlier_ransac_src.size());
	Mat A21 = final_RANSAC(max_inlier_ransac_dst, max_inlier_ransac_src, max_inlier_ransac_src.size());

	std::cout << "Final A12 is \n" << A12 << std::endl;


	const float I1_row = input1.rows;
	const float I1_col = input1.cols;
	const float I2_row = input2.rows;
	const float I2_col = input2.cols;

	Point2f p1(A21.at<float>(0) * 0 + A21.at<float>(1) * 0 + A21.at<float>(2),
		A21.at<float>(3) * 0 + A21.at<float>(4) * 0 + A21.at<float>(5));

	Point2f p2(A21.at<float>(0) * 0 + A21.at<float>(1) * I2_col + A21.at<float>(2),
		A21.at<float>(3) * 0 + A21.at<float>(4) * I2_col + A21.at<float>(5));

	Point2f p3(A21.at<float>(0) * I2_row + A21.at<float>(1) * 0 + A21.at<float>(2),
		A21.at<float>(3) * I2_row + A21.at<float>(4) * 0 + A21.at<float>(5));

	Point2f p4(A21.at<float>(0) * I2_row + A21.at<float>(1) * I2_col + A21.at<float>(2),
		A21.at<float>(3) * I2_row + A21.at<float>(4) * I2_col + A21.at<float>(5));
	// for inverse warping
	Point2f p1_(A12.at<float>(0) * 0 + A12.at<float>(1) * 0 + A12.at<float>(2),
		A12.at<float>(3) * 0 + A12.at<float>(4) * 0 + A12.at<float>(5));

	Point2f p2_(A12.at<float>(0) * 0 + A12.at<float>(1) * I1_col + A12.at<float>(2),
		A12.at<float>(3) * 0 + A12.at<float>(4) * I1_col + A12.at<float>(5));

	Point2f p3_(A12.at<float>(0) * I1_row + A12.at<float>(1) * 0 + A12.at<float>(2),
		A12.at<float>(3) * I1_row + A12.at<float>(4) * 0 + A12.at<float>(5));

	Point2f p4_(A12.at<float>(0) * I1_row + A12.at<float>(1) * I1_col + A12.at<float>(2),
		A12.at<float>(3) * I1_row + A12.at<float>(4) * I1_col + A12.at<float>(5));

	// compute boundary for merged image(I_f)
	int bound_u = (int)round(min(0.0f, min(p1.x, p2.x)));
	int bound_b = (int)round(std::max(I1_row, std::max(p3.x, p4.x)));
	int bound_l = (int)round(min(0.0f, min(p1.y, p3.y)));
	int bound_r = (int)round(std::max(I1_col, std::max(p2.y, p4.y)));

	// compute boundary for inverse warping
	int bound_u_ = (int)round(min(0.0f, min(p1_.x, p2_.x)));
	int bound_b_ = (int)round(std::max(I2_row, std::max(p3_.x, p4_.x)));
	int bound_l_ = (int)round(min(0.0f, min(p1_.y, p3_.y)));
	int bound_r_ = (int)round(std::max(I2_col, std::max(p2_.y, p4_.y)));
	int diff_x = abs(bound_u);
	int diff_y = abs(bound_l);

	int diff_x_ = abs(bound_u_);
	int diff_y_ = abs(bound_l_);

	// initialize merged image
	Mat I_f(bound_b - bound_u + 1, bound_r - bound_l + 1, CV_32FC3, Scalar(0));
	// bilinear interplolation
	for (int i = -diff_x_; i < I_f.rows - diff_x_; i++) {
		for (int j = -diff_y_; j < I_f.cols - diff_y_; j++) {
			float x = A12.at<float>(0) * i + A12.at<float>(1) * j + A12.at<float>(2) + diff_x_;
			float y = A12.at<float>(3) * i + A12.at<float>(4) * j + A12.at<float>(5) + diff_y_;

			float y1 = floor(y);
			float y2 = ceil(y);
			float x1 = floor(x);
			float x2 = ceil(x);

			float mu = y - y1;
			float lambda = x - x1;
			if (x1 >= 0 && x2 < I2_row && y1 >= 0 && y2 < I2_col) {

				Vec3f p1 = input2.at<Vec3f>(x1, y2) * mu + input2.at<Vec3f>(x1, y1) * (1 - mu);
				Vec3f p2 = input2.at<Vec3f>(x2, y2) * mu + input2.at<Vec3f>(x2, y1) * (1 - mu);

				I_f.at<Vec3f>(i + diff_x_, j + diff_y_) = p2 * lambda + p1 * (1 - lambda);

			}
		}
	}

	// image stitching with blend
	blend_stitching(input1, input2, I_f, diff_x, diff_y, 0.5);

	namedWindow("result");
	imshow("result", I_f);

	waitKey(0);
	return 0;
}


//AFFINE TRANSFORMATION ESTIMATION #1-2: k=3
Mat cal_affine(vector<Point2f>& srcPoints, vector<Point2f>& dstPoints, int number_of_points) {

	Mat M(2 * 3, 6, CV_32F, Scalar(0));
	Mat b(2 * 3, 1, CV_32F);

	Mat M_trans, temp, affineM;

	//1. randomly sample k data
	int k1 = rand() % number_of_points;
	int k2 = rand() % number_of_points;
	int k3 = rand() % number_of_points;

	M.at<float>(0, 0) = dstPoints[k1].x;
	M.at<float>(0, 1) = dstPoints[k1].y;
	M.at<float>(0, 2) = 1;

	M.at<float>(1, 3) = dstPoints[k1].x;
	M.at<float>(1, 4) = dstPoints[k1].y;
	M.at<float>(1, 5) = 1;

	M.at<float>(2, 0) = dstPoints[k2].x;
	M.at<float>(2, 1) = dstPoints[k2].y;
	M.at<float>(2, 2) = 1;

	M.at<float>(3, 3) = dstPoints[k2].x;
	M.at<float>(3, 4) = dstPoints[k2].y;
	M.at<float>(3, 5) = 1;

	M.at<float>(4, 0) = dstPoints[k3].x;
	M.at<float>(4, 1) = dstPoints[k3].y;
	M.at<float>(4, 2) = 1;

	M.at<float>(5, 3) = dstPoints[k3].x;
	M.at<float>(5, 4) = dstPoints[k3].y;
	M.at<float>(5, 5) = 1;

	b.at<float>(0, 0) = srcPoints[k1].x;
	b.at<float>(1, 0) = srcPoints[k1].y;
	b.at<float>(2, 0) = srcPoints[k2].x;
	b.at<float>(3, 0) = srcPoints[k2].y;
	b.at<float>(4, 0) = srcPoints[k3].x;
	b.at<float>(5, 0) = srcPoints[k3].y;

	// 2. Estimate the affine transformation T by solving Mx = b
	M_trans = M.t();
	temp = M_trans * M;
	temp = temp.inv();
	temp = temp * M_trans;
	affineM = temp * b;
	return affineM;
}

// AFFINE TRANSFORMATION ESTIMATION #3: Score by computing the number of inliers satisfying
int repeat_RANSAC(vector<Point2f>& srcPoints, vector<Point2f>& dstPoints, vector<Point2f>& ransac_src, vector<Point2f>& ransac_dst, Mat& A12) {

	Mat M_t(2 * srcPoints.size(), 6, CV_32F, Scalar(0));
	Mat b_t(2 * srcPoints.size(), 1, CV_32F);

	for (int i = 0; i < srcPoints.size(); i++) {
		M_t.at<float>((2 * i), 0) = srcPoints[i].x;
		M_t.at<float>((2 * i), 1) = srcPoints[i].y;
		M_t.at<float>((2 * i), 2) = 1;

		M_t.at<float>((2 * i + 1), 3) = srcPoints[i].x;
		M_t.at<float>((2 * i + 1), 4) = srcPoints[i].y;
		M_t.at<float>((2 * i + 1), 5) = 1;

		b_t.at<float>((2 * i), 0) = dstPoints[i].x;
		b_t.at<float>((2 * i + 1), 0) = dstPoints[i].y;
	}
	Mat tempp = M_t*A12 - b_t;

	int num = 0;
	for (int l = 0; l < srcPoints.size(); l++) {

		//get T's inliers
		if ((tempp.at<float>(l, 0) *tempp.at<float>(l, 0)) < 100) {
			num += 1;
			ransac_src.push_back(srcPoints[l]);
			ransac_dst.push_back(dstPoints[l]);
		}
	}
	return num;
}

//AFFINE TRANSFORMATION ESTIMATION #5: Re-estimate the affine transformation
Mat final_RANSAC(vector<Point2f>& srcPoints, vector<Point2f>& dstPoints, int number_of_points) {

	Mat M(2 * number_of_points, 6, CV_32F, Scalar(0));
	Mat b(2 * number_of_points, 1, CV_32F);

	Mat M_trans, temp, affineM;

	for (int i = 0; i < number_of_points; i++) {
		Point2f pt1 = srcPoints[i];
		Point2f pt2 = dstPoints[i];

		M.at<float>((2 * i), 0) = pt2.y;
		M.at<float>((2 * i), 1) = pt2.x;
		M.at<float>((2 * i), 2) = 1;

		M.at<float>((2 * i + 1), 3) = pt2.y;
		M.at<float>((2 * i + 1), 4) = pt2.x;
		M.at<float>((2 * i + 1), 5) = 1;

		b.at<float>((2 * i), 0) = pt1.y;
		b.at<float>((2 * i + 1), 0) = pt1.x;
	}

	// 2. Estimate the affine transformation T by solving Mx = b
	M_trans = M.t();
	temp = M_trans * M;
	temp = temp.inv();
	temp = temp * M_trans;
	affineM = temp * b;
	affineM = affineM.reshape(1, 2);
	return affineM;
}

// FindPairs
double euclidDistance(Mat& vec1, Mat& vec2) {
	double sum = 0.0;
	int dim = vec1.cols;
	for (int i = 0; i < dim; i++) {
		sum += (vec1.at<float>(0, i) - vec2.at<float>(0, i)) * (vec1.at<float>(0, i) - vec2.at<float>(0, i));
	}

	return sqrt(sum);
}
// FindPairs
int nearestNeighbor(Mat& vec, vector<KeyPoint>& keypoints, Mat& descriptors) {
	int neighbor = -1;
	double minDist = 1e6;
	Mat v = descriptors.row(0);      // each row of descriptor
	double min = euclidDistance(vec, v); //compare with descriptor row 0
	for (int i = 1; i < descriptors.rows; i++) {
		v = descriptors.row(i);      // each row of descriptor
		double dist = euclidDistance(vec, v); //compare with descriptor with other row
		if (dist < min) {
			min = dist;
			neighbor = i;
		}
	}

	return neighbor;
}
// FindPairs
int ratio_thresholding(Mat& vec, vector<KeyPoint>& keypoints, Mat& descriptors) {
	double minDist = 1e6;
	double temp;
	Mat v = descriptors.row(0);      // each row of descriptor
	double min = euclidDistance(vec, v);
	v = descriptors.row(1);      // each row of descriptor
	double second = euclidDistance(vec, v);

	if (min > second) {
		temp = second;
		second = min;
		min = temp;
	}
	for (int i = 2; i < descriptors.rows; i++) {
		Mat v = descriptors.row(i);      // each row of descriptor
		double dist = euclidDistance(vec, v);
		if (min > dist) {   //dist is smallest
			temp = min;
			min = dist;
			second = temp;
		}
		else if (second > dist) { //second>dist > min
			second = dist;
		}
	}
	if (min / second < RATIO_THR) {
		return 0;
	}

	return 1;
}

// FindPairs
void findPairs(vector<KeyPoint>& keypoints1, Mat& descriptors1,
	vector<KeyPoint>& keypoints2, Mat& descriptors2,
	vector<Point2f>& srcPoints, vector<Point2f>& dstPoints, bool crossCheck, bool ratio_threshold) {
	int num = 0;
	for (int i = 0; i < descriptors1.rows; i++) {
		KeyPoint pt1 = keypoints1[i];

		Mat desc1 = descriptors1.row(i);
		int nn = nearestNeighbor(desc1, keypoints2, descriptors2);

		// Refine matching points using cross-checking
		if (crossCheck && nn != -1) {
			Mat desc2 = descriptors2.row(nn);
			int check = nearestNeighbor(desc2, keypoints2, descriptors1);
			if (i != check) {
				nn = -1;
			}
		}

		if (ratio_threshold && nn != -1) {
			if (ratio_thresholding(desc1, keypoints2, descriptors2) == 1) {
				nn = -1;
			}
		}

		if (nn != -1) {
			num += 1;
			KeyPoint pt2 = keypoints2[nn];
			srcPoints.push_back(pt1.pt);
			dstPoints.push_back(pt2.pt);
		}
	}

	printf("All nums: %d\n", num);
}

void blend_stitching(const Mat I1, const Mat I2, Mat& I_f, int diff_x, int diff_y, float alpha) {

	int bound_x = I1.rows + diff_x;
	int bound_y = I1.cols + diff_y;

	int col = I_f.cols;
	std::cout << "\nFinal Image col is " << col << std::endl;
	int row = I_f.rows;
	std::cout << "\nFinal Image row is " << row << std::endl;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			bool cond1 = (i < bound_x&& i > diff_x) && (j < bound_y&& j > diff_y) ? true : false;
			bool cond2 = I_f.at<Vec3f>(i, j) != Vec3f(0, 0, 0) ? true : false;

			// I2 is already in I_f by inverse warping
			// So, It is not necessary to check that only I2 is valid
			// if both are valid
			if (cond1 && cond2) {
				I_f.at<Vec3f>(i, j) = alpha * I1.at<Vec3f>(i - diff_x, j - diff_y) + (1 - alpha) * I_f.at<Vec3f>(i, j);
			}
			// only I1 is valid
			else if (cond1) {
				I_f.at<Vec3f>(i, j) = I1.at<Vec3f>(i - diff_x, j - diff_y);
			}
		}
	}
}
