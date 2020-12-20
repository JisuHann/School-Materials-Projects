#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>

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

	Mat input = imread("lena.jpg", IMREAD_COLOR);
	Mat input_gray;
	Mat output;


	cvtColor(input, input_gray, CV_RGB2GRAY);


	if (!input.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	namedWindow("Grayscale", WINDOW_AUTOSIZE);
	imshow("Grayscale", input_gray);
	output = gaussianfilter_r(input_gray, 1, 1, 1, "zero-paddle"); //Boundary process: zero-paddle, mirroring, adjustkernel

	namedWindow("Gaussian Filter", WINDOW_AUTOSIZE);
	imshow("Gaussian Filter", output);


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
	kernel = Mat::zeros(kernel_size,1, CV_32F);
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
		float value_t= exp( - (pow(b, 2) / (2 * pow(sigmaT, 2))));
		kernel2.at<float>(0, b + n) = value_t;
		denom_t += value_t;
	}

	for (int b = -n; b <= n; b++) {
		kernel2.at<float>(0, b + n) /= denom_t;
	}


	Mat output = Mat::zeros(row, col, input.type());


	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {

			float sum1 = 0.0;
			if (!strcmp(opt, "zero-paddle")) {
				for (int a = -n; a <= n; a++) {
					for (int b = -n; b <= n; b++) {

						// Gaussian filter with Zero-paddle boundary process
						if ((i + a <= row - 1) && (i + a >= 0) && (j + b <= col - 1) && (j + b >= 0)) { //if the pixel is not a border pixel
							sum1 += kernel.at<float>(a + n,0)* kernel2.at<float>(0, b + n) * (float)(input.at<G>(i + a, j + b));
						}
					}
				}
				
				output.at<G>(i, j) = (G)sum1;
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
						sum1 += kernel.at<float>(a + n, 0) * kernel2.at<float>(0, b + n) * (float)(input.at<G>(tempa, tempb));

					}
				}
			
				output.at<G>(i, j) = (G)sum1;
			}


			else if (!strcmp(opt, "adjustkernel")) {
				float sum1 = 0.0;
				float sum2 = 0.0;
				for (int a = -n; a <= n; a++) {
					for (int b = -n; b <= n; b++) {

						// Gaussian filter with "adjustkernel" process:
						sum1 += kernel.at<float>(a + n, 0) * kernel2.at<float>(0, b + n) * (float)(input.at<G>(i + a, j + b));
						sum2 += kernel.at<float>(a + n,0) * kernel2.at<float>(0, b + n);

					}
				}
				sum1 = sum1 * 3;
				output.at<G>(i, j) = (G)(sum1 / sum2);
			}
		}
	}
	return output;
}