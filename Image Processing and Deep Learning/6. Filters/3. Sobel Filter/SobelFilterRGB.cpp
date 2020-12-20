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

Mat sobelfilter(const Mat input);

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
	output = sobelfilter(input); //Boundary process: zero-paddle, mirroring, adjustkernel

	namedWindow("Sobel Filter", WINDOW_AUTOSIZE);
	imshow("Sobel Filter", output);


	waitKey(0);

	return 0;
}


Mat sobelfilter(const Mat input) {

	int row = input.rows;
	int col = input.cols;
	int n = 1; // Sobel Filter Kernel N

	// Initialiazing 2 Kernel Matrix with 3x3 size for Sx and Sy
	//Fill code to initialize Sobel filter kernel matrix for Sx and Sy (Given in the lecture notes)
	Mat input2;
	cvtColor(input, input2, CV_RGB2GRAY);
	Mat output = Mat::zeros(row, col, input2.type());
	int kernelx[3][3] = { {-1,0,1},{-2,0,2},{-1,0,1} };
	int kernely[3][3] = { {-1,-2,-1},{0,0,0},{1,2,1} };

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {

			int tempa, tempb;
			float sum_r_x = 0.0, sum_r_y = 0.0, sum_g_x = 0.0, sum_g_y = 0.0, sum_b_x = 0.0, sum_b_y = 0.0;
			float M_r = 0.0, M_g = 0.0, M_b = 0.0;
			for (int a = -n; a <= n; a++) {
				for (int b = -n; b <= n; b++) {
					// Use mirroring boundary process
					// Find output M(x,y) = sqrt( input.at<G>(x, y)*Sx + input.at<G>(x, y)*Sy )
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
					sum_r_x += (float)kernelx[a + n][b + n] * (float)(input.at<C>(tempa, tempb)[0]);
					sum_r_y += (float)kernely[a + n][b + n] * (float)(input.at<C>(tempa, tempb)[0]);
					sum_g_x += (float)kernelx[a + n][b + n] * (float)(input.at<C>(tempa, tempb)[1]);
					sum_g_y += (float)kernely[a + n][b + n] * (float)(input.at<C>(tempa, tempb)[1]);
					sum_b_x += (float)kernelx[a + n][b + n] * (float)(input.at<C>(tempa, tempb)[2]);
					sum_b_y += (float)kernely[a + n][b + n] * (float)(input.at<C>(tempa, tempb)[2]);
				}

			}
			M_r = pow(sum_r_x, 2) + pow(sum_r_y, 2);
			M_r = sqrt(M_r);
			if (M_r >= 255) M_r = 255;

			M_g = pow(sum_g_x, 2) + pow(sum_g_y, 2);
			M_g = sqrt(M_g);
			if (M_g >= 255) M_g = 255;

			M_b = pow(sum_b_x, 2) + pow(sum_b_y, 2);
			M_b = sqrt(M_b);
			if (M_b >= 255) M_b = 255;
			output.at<G>(i, j) = (G)((M_b+M_r+M_g)/3);
		}
	}
	return output;
}