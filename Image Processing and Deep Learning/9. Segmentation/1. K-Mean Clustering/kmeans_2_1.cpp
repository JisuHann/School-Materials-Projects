#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#define IM_TYPE	CV_8UC3
using namespace cv;

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


	Mat samples(input.rows * input.cols, 3, CV_32F);
	for (int y = 0; y < input.rows; y++) {
		for (int x = 0; x < input.cols; x++) {
			samples.at<float>(y + x * input.rows, 0) = ((float)input.at<Vec3b>(y, x)[0]);
			samples.at<float>(y + x * input.rows, 1) = ((float)input.at<Vec3b>(y, x)[1]);
			samples.at<float>(y + x * input.rows, 2) = ((float)input.at<Vec3b>(y, x)[2]);
		}
	}
	int clusterCount = 10;
	Mat labels;
	int attempts = 5;
	Mat centers;
	kmeans(samples, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers);

	Mat new_image(input.size(), input.type());
	for (int y = 0; y < input.rows; y++)
		for (int x = 0; x < input.cols; x++)
		{
			int cluster_idx = labels.at<int>(y + x * input.rows, 0);
			new_image.at<Vec3b>(y, x)[0] = (uchar) centers.at<float>(cluster_idx, 0);
			new_image.at<Vec3b>(y, x)[1] = (uchar) centers.at<float>(cluster_idx, 1);
			new_image.at<Vec3b>(y, x)[2] = (uchar) centers.at<float>(cluster_idx, 2);
		}
	imshow("clustered image", new_image);

	waitKey(0);

	return 0;
}