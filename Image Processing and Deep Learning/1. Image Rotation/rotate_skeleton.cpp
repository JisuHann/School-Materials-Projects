#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

template <typename T>
Mat myrotate(const Mat input, float angle, const char* opt);

int main()
{
	Mat input, rotated, rotated2;
	String filename = "C:\\lena.jpg";
	input = imread(filename, IMREAD_COLOR);											

	// Check for invalid input
	if (!input.data) {
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	// original image
	namedWindow("image");
	imshow("image", input);

	rotated = myrotate<Vec3b>(input, 45, "nearest");

	// rotated image
	namedWindow("Nearest Neighboor Interpolation - rotated");
	imshow("Nearest Neighboor Interpolation - rotated", rotated);

	rotated2 = myrotate<Vec3b>(input, 45, "bilinear");
	// rotated image
	namedWindow("Bilinear Interpolation - rotated");
	imshow("Bilinear Interpolation - rotated", rotated2);

	waitKey(0);

	return 0;
}

template <typename T>
Mat myrotate(const Mat input, float angle, const char* opt) {
	int row = input.rows;
	int col = input.cols;

	float radian = angle * CV_PI / 180;

	float sq_row = ceil(row * sin(radian) + col * cos(radian));
	float sq_col = ceil(col * sin(radian) + row * cos(radian));				

	Mat output = Mat::zeros(sq_row, sq_col, input.type());

	for (int i = 0; i < sq_row; i++) {
		for (int j = 0; j < sq_col; j++) {
			float x = (j - sq_col / 2) * cos(radian) - (i - sq_row / 2) * sin(radian) + col / 2;
			float y = (j - sq_col / 2) * sin(radian) + (i - sq_row / 2) * cos(radian) + row / 2;

			if ((y >= 0) && (y <= (row - 1)) && (x >= 0) && (x <= (col - 1))) {
				float x_gap = x - int(x);
				float y_gap = y - int(y);
				if (!strcmp(opt, "nearest")) {
					//Nearest Neighboor Interpolation: selecting different vector value according to x_gap and y_gap
					if ((x_gap <= 0.5) and (y_gap <= 0.5)) {
						output.at<Vec3b>(i, j) = input.at<Vec3b>(floor(y), floor(x));
					}
					if ((x_gap <= 0.5) and (y_gap > 0.5)) {
						output.at<Vec3b>(i, j) = input.at<Vec3b>(floor(y), ceil(x));
					}
					if ((x_gap > 0.5) and (y_gap <= 0.5)) {
						output.at<Vec3b>(i, j) = input.at<Vec3b>(ceil(y), floor(x)); 
					}
					if ((x_gap > 0.5) and (y_gap > 0.5)) {
						output.at<Vec3b>(i, j) = input.at<Vec3b>(ceil(y), ceil(x));
					}

				}
				else if (!strcmp(opt, "bilinear")) {
					//bilinear Interpolation: Use the y_gap first, and select the value depending on x_gap
					Vec3b p1 = input.at<Vec3b>(floor(y), ceil(x)) * y_gap + input.at<Vec3b>(floor(y), floor(x)) * (1-y_gap);
					Vec3b p2 = input.at<Vec3b>(ceil(y), ceil(x)) * y_gap + input.at<Vec3b>(ceil(y), floor(x)) * (1 - y_gap);

					output.at<Vec3b>(i, j) = p2 * x_gap + p1 * (1 - x_gap);
				}
			}
			
		}
	}
	std::cout << "Operation Success" << std::endl;
	return output;
}