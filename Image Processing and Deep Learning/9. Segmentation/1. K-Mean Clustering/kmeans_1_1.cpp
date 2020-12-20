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

	Mat samples(input_gray.rows * input_gray.cols, 1, CV_32F);
	for (int y = 0; y < input_gray.rows; y++) {
		for (int x = 0; x < input_gray.cols; x++) {
			samples.at<float>(y + x * input_gray.rows, 0) = (float)input_gray.at<uchar>(y, x);

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
	for (int y = 0; y < input_gray.rows; y++) {
		for (int x = 0; x < input_gray.cols; x++)
		{
			int cluster_idx = labels.at<int>(y + x * input_gray.rows, 0);
			new_image.at<uchar>(y, x) = (uchar)(centers.at<float>(cluster_idx, 0));
		}
	}

	namedWindow("New Image", WINDOW_AUTOSIZE);
	imshow("New Image", new_image);
	waitKey(0);

	return 0;
}

