// opencv_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/imgproc/types_c.h>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;


Mat get_Gaussian_Kernel(int n, double sigma_t, double sigma_s, bool normalize);
Mat get_Laplacian_Kernel();
Mat Gaussianfilter(const Mat input, int n, double sigma_t, double sigma_s);
Mat Laplacianfilter(const Mat input);
Mat Mirroring(const Mat input, int n);


int main() {

	Mat input = imread("lena.jpg", IMREAD_COLOR);

	// check for validation
	if (!input.data) {
		printf("Could not open\n");
		return -1;
	}

	//Gaussian smoothing parameters
	int window_radius = 2;
	double sigma_t = 2.0;
	double sigma_s = 2.0;

	input.convertTo(input, CV_64F, 1.0 / 255);	// 8-bit unsigned char -> 64-bit floating point

	Mat h_f = Gaussianfilter(input, window_radius, sigma_t, sigma_s);	// h(x,y) * f(x,y)
	Mat Laplacian = Laplacianfilter(h_f);

	normalize(Laplacian, Laplacian, 0, 1, CV_MINMAX);

	namedWindow("Color Image", WINDOW_AUTOSIZE);
	imshow("Color Image", input);

	namedWindow("Gaussian blur", WINDOW_AUTOSIZE);
	imshow("Gaussian blur", h_f);

	namedWindow("Laplacian filter", WINDOW_AUTOSIZE);
	imshow("Laplacian filter", Laplacian);

	waitKey(0);

	return 0;
}



Mat Gaussianfilter(const Mat input, int n, double sigma_t, double sigma_s) {

	int row = input.rows;
	int col = input.cols;

	// generate gaussian kernel
	Mat kernel = get_Gaussian_Kernel(n, sigma_t, sigma_s, true);
	Mat output = Mat::zeros(row, col, input.type());

	//Intermediate data generation for mirroring
	Mat input_mirror = Mirroring(input, n);

	for (int i = 0; i < row ; i++) {
		for (int j = 0; j < col; j++) {

			double sum_r = 0.0, sum_g = 0.0, sum_b = 0.0;
			for (int a = -n; a <= n; a++) {
				for (int b = -n; b <= n; b++) {
					sum_r += kernel.at<double>(a + n, b + n) * ((double)input_mirror.at<Vec3d>(i + a + n, j + b + n)[0]);
					sum_g += kernel.at<double>(a + n, b + n) * ((double)input_mirror.at<Vec3d>(i + a + n, j + b + n)[1]);
					sum_b += kernel.at<double>(a + n, b + n) * ((double)input_mirror.at<Vec3d>(i + a + n, j + b + n)[2]);
				}
			}
			output.at<Vec3d>(i, j)[0] = (double)sum_r;
			output.at<Vec3d>(i, j)[1] = (double)sum_g;
			output.at<Vec3d>(i, j)[2] = (double)sum_b;


		}
	}

	return output;
}

Mat Laplacianfilter(const Mat input) {

	int row = input.rows;
	int col = input.cols;

	Mat kernel = get_Laplacian_Kernel();
	Mat output = Mat::zeros(row, col, CV_64F);

	int n = 1;
	Mat input_mirror = Mirroring(input, n);

	for (int i = 0; i < row ; i++) {
		for (int j =0; j < col ; j++) {

			double sum_r = 0.0, sum_g = 0.0, sum_b = 0.0;
			for (int a = -n; a <= n; a++) {
				for (int b = -n; b <= n; b++) {
					sum_r += kernel.at<double>(a + n, b + n) * ((double)input_mirror.at<Vec3d>(i + a + n, j + b + n)[0]);
					sum_g += kernel.at<double>(a + n, b + n) * ((double)input_mirror.at<Vec3d>(i + a + n, j + b + n)[1]);
					sum_b += kernel.at<double>(a + n, b + n) * ((double)input_mirror.at<Vec3d>(i + a + n, j + b + n)[2]);
				}
			}
			if (sum_r < 0)sum_r = -sum_r;
			if (sum_r > 255) sum_r = 255;

			if (sum_g < 0)sum_g = -sum_g;
			if (sum_g > 255) sum_g = 255;

			if (sum_b < 0)sum_b = -sum_b;
			if (sum_b > 255) sum_b = 255;
			output.at<double>(i, j) = (double)(sum_r+sum_g+sum_b)/3;

		}
	}

	return output;
}

Mat Mirroring(const Mat input, int n)
{
	int row = input.rows;
	int col = input.cols;

	Mat input2 = Mat::zeros(row + 2 * n, col + 2 * n, input.type());
	int row2 = input2.rows;
	int col2 = input2.cols;

	for (int i = n; i < row + n; i++) {
		for (int j = n; j < col + n; j++) {
			input2.at<Vec3d>(i, j)[0] = (double)input.at<Vec3d>(i - n, j - n)[0];
			input2.at<Vec3d>(i, j)[1] = (double)input.at<Vec3d>(i - n, j - n)[1];
			input2.at<Vec3d>(i, j)[2] = (double)input.at<Vec3d>(i - n, j - n)[2];
		}
	}
	for (int i = n; i < row + n; i++) {
		for (int j = 0; j < n; j++) {
			input2.at<Vec3d>(i, j)[0] = (double)input2.at<Vec3d>(i, 2 * n - j)[0];
			input2.at<Vec3d>(i, j)[1] = (double)input2.at<Vec3d>(i, 2 * n - j)[1];
			input2.at<Vec3d>(i, j)[2] = (double)input2.at<Vec3d>(i, 2 * n - j)[2];
		}
		for (int j = col + n; j < col2; j++) {
			input2.at<Vec3d>(i, j)[0] = (double)input2.at<Vec3d>(i, 2 * col - 2 + 2 * n - j)[0];
			input2.at<Vec3d>(i, j)[1] = (double)input2.at<Vec3d>(i, 2 * col - 2 + 2 * n - j)[1];
			input2.at<Vec3d>(i, j)[2] = (double)input2.at<Vec3d>(i, 2 * col - 2 + 2 * n - j)[2];
		}
	}
	for (int j = 0; j < col2; j++) {
		for (int i = 0; i < n; i++) {
			input2.at<Vec3d>(i, j)[0] = (double)input2.at<Vec3d>(2 * n - i, j)[0];
			input2.at<Vec3d>(i, j)[1] = (double)input2.at<Vec3d>(2 * n - i, j)[1];
			input2.at<Vec3d>(i, j)[2] = (double)input2.at<Vec3d>(2 * n - i, j)[2];
		}
		for (int i = row + n; i < row2; i++) {
			input2.at<Vec3d>(i, j)[0] = (double)input2.at<Vec3d>(2 * row - 2 + 2 * n - i, j)[0];
			input2.at<Vec3d>(i, j)[1] = (double)input2.at<Vec3d>(2 * row - 2 + 2 * n - i, j)[1];
			input2.at<Vec3d>(i, j)[2] = (double)input2.at<Vec3d>(2 * row - 2 + 2 * n - i, j)[2];
		}
	}

	return input2;
}


Mat get_Gaussian_Kernel(int n, double sigma_t, double sigma_s, bool normalize) {

	int kernel_size = (2 * n + 1);
	Mat kernel = Mat::zeros(kernel_size, kernel_size, CV_64F);
	double kernel_sum = 0.0;

	for (int i = -n; i <= n; i++) {
		for (int j = -n; j <= n; j++) {
			kernel.at<double>(i + n, j + n) = exp(-((i * i) / (2.0 * sigma_t * sigma_t) + (j * j) / (2.0 * sigma_s * sigma_s)));
			kernel_sum += kernel.at<double>(i + n, j + n);
		}
	}

	if (normalize) {
		for (int i = 0; i < kernel_size; i++)
			for (int j = 0; j < kernel_size; j++)
				kernel.at<double>(i, j) /= kernel_sum;		// normalize
	}

	return kernel;
}

Mat get_Laplacian_Kernel() {

	Mat kernel = Mat::zeros(3, 3, CV_64F);

	kernel.at<double>(0, 1) = 1.0;
	kernel.at<double>(2, 1) = 1.0;
	kernel.at<double>(1, 0) = 1.0;
	kernel.at<double>(1, 2) = 1.0;
	kernel.at<double>(1, 1) = -4.0;

	return kernel;
}