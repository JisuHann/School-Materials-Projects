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

int main() {

	Mat input1 = imread("C:\\input1.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input2 = imread("C:\\input2.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input1_gray, input2_gray;

	if (!input1.data || !input2.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	//resize(input1, input1, Size(input1.cols / 2, input1.rows / 2));
	//resize(input2, input2, Size(input2.cols / 2, input2.rows / 2));

	cvtColor(input1, input1_gray, CV_RGB2GRAY);
	cvtColor(input2, input2_gray, CV_RGB2GRAY);

	FeatureDetector* detector = new SiftFeatureDetector(
		0,		// nFeatures
		4,		// nOctaveLayers
		0.04,	// contrastThreshold
		10,		// edgeThreshold
		1.6		// sigma
	);

	DescriptorExtractor* extractor = new SiftDescriptorExtractor();

	// Create a image for displaying mathing keypoints
	Size size = input2.size();
	Size sz = Size(size.width + input1_gray.size().width, max(size.height, input1_gray.size().height));
	Mat matchingImage = Mat::zeros(sz, CV_8UC3);

	input1.copyTo(matchingImage(Rect(size.width, 0, input1_gray.size().width, input1_gray.size().height)));
	input2.copyTo(matchingImage(Rect(0, 0, size.width, size.height)));
	
	// Compute keypoints and descriptor from the source image in advance
	vector<KeyPoint> keypoints1;
	Mat descriptors1;

	detector->detect(input1_gray, keypoints1);
	extractor->compute(input1_gray, keypoints1, descriptors1);
	printf("input1 : %d keypoints are found.\n", (int)keypoints1.size());

	vector<KeyPoint> keypoints2;
	Mat descriptors2;

	// Detect keypoints
	detector->detect(input2_gray, keypoints2);
	extractor->compute(input2_gray, keypoints2, descriptors2);

	printf("input2 : %zd keypoints are found.\n", keypoints2.size());

	for (int i = 0; i < keypoints1.size(); i++) {
		KeyPoint kp = keypoints1[i];
		kp.pt.x += size.width;
		circle(matchingImage, kp.pt, cvRound(kp.size*0.25), Scalar(255, 255, 0), 1, 8, 0);
	}

	for (int i = 0; i < keypoints2.size(); i++) {
		KeyPoint kp = keypoints2[i];
		circle(matchingImage, kp.pt, cvRound(kp.size*0.25), Scalar(255, 255, 0), 1, 8, 0);
	}
	printf("input1 : %zd keypoints %d %d descriptors.\n", keypoints1.size(), descriptors1.size().height, descriptors1.size().width);
	printf("input2 : %zd keypoints %d %d descriptors.\n", keypoints2.size(),descriptors2.size().height, descriptors2.size().width);


	// Find nearest neighbor pairs
	
	vector<Point2f> srcPoints;
	vector<Point2f> dstPoints;
	bool crossCheck = true;
	bool ratio_threshold = true;
//	findPairs(keypoints1, descriptors1, keypoints2, descriptors2, srcPoints, dstPoints, crossCheck, ratio_threshold);
	findPairs(keypoints2, descriptors2, keypoints1, descriptors1, srcPoints, dstPoints, crossCheck, ratio_threshold);
	printf("%zd keypoints are matched.\n", srcPoints.size());

	// Draw line between nearest neighbor pairs
	for (int i = 0; i < (int)srcPoints.size(); ++i) {
		Point2f pt1 = srcPoints[i];
		Point2f pt2 = dstPoints[i];
		Point2f from = pt1;
		Point2f to = Point(size.width + pt2.x, pt2.y);
		line(matchingImage, from, to, Scalar(0, 0, 255));
	}

	// Display mathing image
	namedWindow("Matching");
	imshow("Matching", matchingImage);
	
	waitKey(0);
	return 0;
}

/**
* Calculate euclid distance
*/
double euclidDistance(Mat& vec1, Mat& vec2) {
	double sum = 0.0;
	int dim = vec1.cols; 
	for (int i = 0; i < dim; i++) {
		sum += (vec1.at<float>(0, i) - vec2.at<float>(0, i)) * (vec1.at<float>(0, i) - vec2.at<float>(0, i));
		//sum += (vec1.at<uchar>(0, i) - vec2.at<uchar>(0, i)) * (vec1.at<uchar>(0, i) - vec2.at<uchar>(0, i));
	}

	return sqrt(sum);
}

/**
* Find the index of nearest neighbor point from keypoints.
https://opencv-python-tutroals.readthedocs.io/en/latest/py_tutorials/py_feature2d/py_matcher/py_matcher.html
*/
int nearestNeighbor(Mat& vec, vector<KeyPoint>& keypoints, Mat& descriptors) {
	int neighbor =-1;
	double minDist = 1e6;
	Mat v = descriptors.row(0);		// each row of descriptor
	double min = euclidDistance(vec, v); //compare with descriptor row 0
	for (int i =1; i < descriptors.rows; i++) {
		v = descriptors.row(i);		// each row of descriptor
		double dist = euclidDistance(vec, v); //compare with descriptor with other row
		if (dist < min) {
			min = dist;
			neighbor = i;
		}
	}

	return neighbor;
}

int ratio_thresholding(Mat& vec, vector<KeyPoint>& keypoints, Mat& descriptors) {
	double minDist = 1e6;
	double temp;
	Mat v = descriptors.row(0);		// each row of descriptor
	double min = euclidDistance(vec, v);
	v = descriptors.row(1);		// each row of descriptor
	double second = euclidDistance(vec, v);

	if (min > second) {
		temp = second;
		second = min;
		min = temp;
	}
	for (int i = 2; i < descriptors.rows; i++) {
		Mat v = descriptors.row(i);		// each row of descriptor
		double dist = euclidDistance(vec, v);
		if (min > dist) {	//dist is smallest
			temp = min;
			min = dist;
			second = temp;
		}
		else if (second > dist) { //second>dist > min 
			second = dist;
		}
	}
	printf("%f\n", min / second);
	if(min /second < 0.3) {
		return 0;
	}
	 
	return 1;
}

/**
* Find pairs of points with the smallest distace between them
*/
void findPairs(vector<KeyPoint>& keypoints1, Mat& descriptors1,
	vector<KeyPoint>& keypoints2, Mat& descriptors2,
	vector<Point2f>& srcPoints, vector<Point2f>& dstPoints, bool crossCheck, bool ratio_threshold) {
	int num = 0;
	for (int i = 0; i < descriptors1.rows; i++) {
		KeyPoint pt1 = keypoints1[i];
		Mat desc1 = descriptors1.row(i);
		int nn	= nearestNeighbor(desc1, keypoints2, descriptors2);

		// Refine matching points using cross-checking
		if (crossCheck && nn != -1) {
			Mat desc2 = descriptors2.row(nn);
			int check = nearestNeighbor(desc2, keypoints2, descriptors1);
			if (i != check) {
				nn = -1;
			}	
		}
		
		if (ratio_threshold && nn != -1) {
			if (ratio_thresholding(desc1, keypoints2, descriptors2)==0) {
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

