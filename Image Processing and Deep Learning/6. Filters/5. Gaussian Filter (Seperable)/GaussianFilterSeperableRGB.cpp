#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <ctime>
#include <math.h>       /* exp */
#define IM_TYPE	CV_8UC3

using namespace cv;

// Image Type
// "G" for GrayScale Image, "C" for Color Image
#if (IM_TYPE == CV_8UC3)
typedef uchar G;
typedef cv::Vec3b C;
#elif (IM_TYPE == CV_16SC3)
typedef short G;
typedef Vec3s C;
#elif (IM_TYPE == CV_32SC3)
typedef int G;
typedef Vec3i C;
#elif (IM_TYPE == CV_32FC3)
typedef float G;
typedef Vec3f C;
#elif (IM_TYPE == CV_64FC3)
typedef double G;
typedef Vec3d C;
#endif

Mat gaussianfilter_r(const Mat input, int n, float sigmaT, float sigmaS, const char* opt);

int main() {

	clock_t start, end;

	start = clock();
	Mat input = imread("C:\\lena.jpg", IMREAD_COLOR);
	Mat output;

	if (!input.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	namedWindow("Original", WINDOW_AUTOSIZE);
	imshow("Original", input);
	output = gaussianfilter_r(input, 1, 1, 1, "zero-paddle"); //Boundary process: zero-paddle, mirroring, adjustkernel

	namedWindow("Gaussian Filter", WINDOW_AUTOSIZE);
	imshow("Gaussian Filter", output);

	end = clock();
	std::cout << "Using Gaussian Seperable function, it took " << (float)start / CLOCKS_PER_SEC << " seconds" << std::endl;
	waitKey(0);

	return 0;
}


Mat gaussianfilter_r(const Mat input, int n, float sigmaT, float sigmaS, const char* opt) {

	Mat kernel, kernel2;

	int row = input.rows;
	int col = input.cols;
	int kernel_size = (2 * n + 1);
	int tempa;
	int tempb;
	float denom_s, denom_t;
	float kernelvalue;

	// Initialiazing Kernel Matrix 
	kernel = Mat::zeros(kernel_size, 1, CV_32F);
	kernel2 = Mat::zeros(1, kernel_size, CV_32F);

	//w(s)
	denom_s = 0.0;
	for (int a = -n; a <= n; a++) {  // Denominator in m(s,t)
		float value_s = exp(-(pow(a, 2) / (2 * pow(sigmaS, 2))));
		kernel.at<float>(a + n, 0) = value_s;
		denom_s += value_s;
	}

	for (int a = -n; a <= n; a++) {  // Denominator in m(s,t)
		kernel.at<float>(a + n, 0) /= denom_s;

	}

	//w(t)
	denom_t = 0.0;
	for (int b = -n; b <= n; b++) {
		float value_t = exp(-(pow(b, 2) / (2 * pow(sigmaT, 2))));
		kernel2.at<float>(0, b + n) = value_t;
		denom_t += value_t;
	}

	for (int b = -n; b <= n; b++) {
		kernel2.at<float>(0, b + n) /= denom_t;
	}

	Mat output = Mat::zeros(row, col, input.type());


	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {

			float sum_r = 0.0, sum_g = 0.0, sum_b = 0.0;
			if (!strcmp(opt, "zero-paddle")) {
				for (int a = -n; a <= n; a++) {
					for (int b = -n; b <= n; b++) {

						// Gaussian filter with Zero-paddle boundary process
						if ((i + a <= row - 1) && (i + a >= 0) && (j + b <= col - 1) && (j + b >= 0)) { //if the pixel is not a border pixel
							sum_r += kernel.at<float>(a + n, 0) * kernel2.at<float>(0, b + n) * (float)(input.at<C>(i + a, j + b)[0]);
							sum_g += kernel.at<float>(a + n, 0) * kernel2.at<float>(0, b + n) * (float)(input.at<C>(i + a, j + b)[1]);
							sum_b += kernel.at<float>(a + n, 0) * kernel2.at<float>(0, b + n) * (float)(input.at<C>(i + a, j + b)[2]);
						}
					}
				}
				output.at<C>(i, j)[0] = (G)sum_r;
				output.at<C>(i, j)[1] = (G)sum_g;
				output.at<C>(i, j)[2] = (G)sum_b;
			}
			else if (!strcmp(opt, "mirroring")) {
				for (int a = -n; a <= n; a++) {
					for (int b = -n; b <= n; b++) {

						// Gaussian filter with "mirroring" process:
						if (i + a > row - 1) {  //mirroring for the border pixels
							tempa = i - a;
						}
						else if (i + a < 0) {
							tempa = -(i + a);
						}
						else {
							tempa = i + a;
						}
						if (j + b > col - 1) {
							tempb = j - b;
						}
						else if (j + b < 0) {
							tempb = -(j + b);
						}
						else {
							tempb = j + b;
						}
						sum_r += kernel.at<float>(a + n, 0) * kernel2.at<float>(0, b + n) * (float)(input.at<C>(tempa, tempb)[0]);
						sum_g += kernel.at<float>(a + n, 0) * kernel2.at<float>(0, b + n) * (float)(input.at<C>(tempa, tempb)[1]);
						sum_b += kernel.at<float>(a + n, 0) * kernel2.at<float>(0, b + n) * (float)(input.at<C>(tempa, tempb)[2]);
					}
				}

				output.at<C>(i, j)[0] = (G)sum_r;
				output.at<C>(i, j)[1] = (G)sum_g;
				output.at<C>(i, j)[2] = (G)sum_b;
			}


			else if (!strcmp(opt, "adjustkernel")) {
				float sum_r_1 = 0.0, sum_g_1=0.0,sum_b_1=0.0;
				float sum_2=0.0;
				for (int a = -n; a <= n; a++) {
					for (int b = -n; b <= n; b++) {

						// Gaussian filter with "adjustkernel" process:
						sum_r_1 += kernel.at<float>(a + n, 0) * kernel2.at<float>(0, b + n) * (float)(input.at<C>(i + a, j + b)[0]);
						sum_g_1 += kernel.at<float>(a + n, 0) * kernel2.at<float>(0, b + n) * (float)(input.at<C>(i + a, j + b)[1]);
						sum_b_1 += kernel.at<float>(a + n, 0) * kernel2.at<float>(0, b + n) * (float)(input.at<C>(i + a, j + b)[2]);
						sum_2 += kernel.at<float>(a + n, 0) * kernel2.at<float>(0, b + n);

					}
				}
			
				output.at<C>(i, j)[0] = (G)(sum_r_1 / sum_2);
				output.at<C>(i, j)[1] = (G)(sum_g_1 / sum_2);
				output.at<C>(i, j)[2] = (G)(sum_b_1 / sum_2);
			}
		}
	}
	return output;
}