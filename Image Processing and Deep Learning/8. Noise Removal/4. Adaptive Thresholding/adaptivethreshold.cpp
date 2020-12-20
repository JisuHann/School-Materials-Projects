#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>

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

Mat adaptive_thres(const Mat input, int n, float b);

int main() {

	Mat input = imread("writing.jpg", IMREAD_COLOR);
	Mat input_gray;
	Mat output;

	cvtColor(input, input_gray, CV_RGB2GRAY); // Converting image to gray


	if (!input.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	namedWindow("Grayscale", WINDOW_AUTOSIZE);
	imshow("Grayscale", input_gray);

	output = adaptive_thres(input_gray, 2, 1.5); 

	namedWindow("Adaptive", WINDOW_AUTOSIZE);
	imshow("Adaptive", output);


	waitKey(0);

	return 0;
}


Mat adaptive_thres(const Mat input, int n, float bnumber) {

	Mat kernel;

	int row = input.rows;
	int col = input.cols;
	int kernel_size = (2 * n + 1);

	kernel = Mat::ones(kernel_size, kernel_size, CV_32F) / (float)(kernel_size * kernel_size);
	float kernelvalue = kernel.at<float>(0, 0); 
	Mat output = Mat::zeros(row, col, input.type());

	for (int i = 0; i < row; i++) { //for each pixel in the output
		for (int j = 0; j < col; j++) {

			float sum1 = 0.0;
			for (int a = -n; a <= n; a++) {
				for (int b = -n; b <= n; b++) {
					if ((a + i >= 0) && (a + i <= row - 1) && (b + j >= 0) && (b + j <= col - 1)) {
						sum1 += input.at<G>(a + i, b + j);
					}
				}
			}

			sum1 = sum1 / ((float)kernel_size * kernel_size);
			float temp = bnumber*(G)sum1;
			if (temp > 255) temp = 255;
			if (temp < 0) temp = 0;

			output.at<G>(i, j) = temp;

		}
	}
	return output;
}