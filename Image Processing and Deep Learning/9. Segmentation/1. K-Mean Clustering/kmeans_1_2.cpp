#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#define IM_TYPE	CV_8UC3
typedef uchar G;
typedef cv::Vec3b C;
using namespace cv;

int main() {

	Mat input = imread("lena.jpg", IMREAD_COLOR);
	Mat input_gray;
	Mat output;

	cvtColor(input, input_gray, CV_RGB2GRAY);

	if (!input.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	namedWindow("Original", WINDOW_AUTOSIZE);
	imshow("Original", input_gray);


	float sigma = 100.0;
	Mat normalized;
	input_gray.convertTo(normalized, CV_32F, 1.0/255);
	Mat samples(normalized.rows * normalized.cols, 3, CV_32F);
	for (int y = 0; y < normalized.rows; y++) {
		for (int x = 0; x < normalized.cols; x++) {
			samples.at<float>(y + x * input_gray.rows, 0) = (float)normalized.at<float>(y,x);
			samples.at<float>(y + x * input_gray.rows, 1) = (float)y /(float)normalized.rows/sigma;
			samples.at<float>(y + x * input_gray.rows, 2) = (float)x /(float)normalized.cols/sigma;

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

	Mat new_image = Mat::zeros(input_gray.size(), input_gray.type());
	for (int y = 0; y < normalized.rows; y++) {
		for (int x = 0; x < normalized.cols; x++)
		{
			int cluster_idx = labels.at<int>(y + x * normalized.rows, 0);
			new_image.at<uchar>(y, x) = (uchar)(centers.at<float>(cluster_idx, 0) * 255);
		}
	}

	namedWindow("New Image", WINDOW_AUTOSIZE);
	imshow("New Image", new_image);
	waitKey(0);

	return 0;
}

