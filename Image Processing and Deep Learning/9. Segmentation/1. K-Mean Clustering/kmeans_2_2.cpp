#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#define IM_TYPE	CV_8UC3
typedef uchar G;
typedef cv::Vec3b C;


using namespace cv;


// Note that this code is for the case when an input data is a color value.
int main() {

	Mat input = imread("lena.jpg", IMREAD_COLOR);
	Mat output;

	if (!input.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	namedWindow("Original", WINDOW_AUTOSIZE);
	imshow("Original", input);


	float sigma = 100.0;
	Mat normalized;

	input.convertTo(normalized, CV_32F, 1.0 / 255);
	Mat samples(normalized.rows * normalized.cols, 5, CV_32F);
	for (int y = 0; y < input.rows; y++) {
		for (int x = 0; x < input.cols; x++) {
			samples.at<float>(y + x * input.rows, 0) = ((float)input.at<Vec3b>(y, x)[0]) / 255;
			samples.at<float>(y + x * input.rows, 1) = ((float)input.at<Vec3b>(y, x)[1]) / 255;
			samples.at<float>(y + x * input.rows, 2) = ((float)input.at<Vec3b>(y, x)[2]) / 255;
			samples.at<float>(y + x * input.rows, 3) = (float)y / (float)input.rows / sigma;
			samples.at<float>(y + x * input.rows, 4) = (float)x / (float)input.cols / sigma;

		}
	}

	int clusterCount = 10;
	Mat labels;
	int attempts = 5;
	Mat centers;

	kmeans(samples, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers);
	//labels: 라벨 결괏값 저장
	//centers: k개의 mean 결괏값들
	//samples: 입력 데이터
	Mat new_image = Mat::zeros(input.size(), input.type());
	for (int y = 0; y < input.rows; y++) {
		for (int x = 0; x < input.cols; x++)
		{
			int cluster_idx = labels.at<int>(y + x * input.rows, 0);
			new_image.at<Vec3b>(y, x)[0] = (uchar)(centers.at<float>(cluster_idx, 0) * 255);
			new_image.at<Vec3b>(y, x)[1] = (uchar)(centers.at<float>(cluster_idx, 1) * 255);
			new_image.at<Vec3b>(y, x)[2] = (uchar)(centers.at<float>(cluster_idx, 2) * 255);
		}
	}

	namedWindow("New Image", WINDOW_AUTOSIZE);
	imshow("New Image", new_image);
	waitKey(0);

	return 0;
}

