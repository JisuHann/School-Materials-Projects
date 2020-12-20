#include "hist_func.h"
#include <opencv2/imgproc/types_c.h>

void hist_eq_Color(Mat &input, Mat &equalized, G(*trans_func)[3], float **CDF);

int main() {

	Mat input = imread("C:\\input.jpg", IMREAD_COLOR);
	Mat equalized_RGB = input.clone();

	// PDF or transfer function txt files
	FILE* f_equalized_PDF_RGB_R, * f_equalized_PDF_RGB_G, * f_equalized_PDF_RGB_B, * f_PDF_RGB_R, * f_PDF_RGB_G, * f_PDF_RGB_B;
	FILE* f_trans_func_eq_RGB_R, * f_trans_func_eq_RGB_G, * f_trans_func_eq_RGB_B;

	fopen_s(&f_PDF_RGB_R, "PDF_RGB_R.txt", "w+");
	fopen_s(&f_PDF_RGB_G, "PDF_RGB_G.txt", "w+");
	fopen_s(&f_PDF_RGB_B, "PDF_RGB_B.txt", "w+");
	fopen_s(&f_equalized_PDF_RGB_R, "equalized_PDF_RGB_R.txt", "w+");
	fopen_s(&f_equalized_PDF_RGB_G, "equalized_PDF_RGB_G.txt", "w+");
	fopen_s(&f_equalized_PDF_RGB_B, "equalized_PDF_RGB_B.txt", "w+");
	fopen_s(&f_trans_func_eq_RGB_R, "trans_func_eq_RGB_R.txt", "w+");
	fopen_s(&f_trans_func_eq_RGB_G, "trans_func_eq_RGB_G.txt", "w+");
	fopen_s(&f_trans_func_eq_RGB_B, "trans_func_eq_RGB_B.txt", "w+");

	float **PDF_RGB = cal_PDF_RGB(input);	// PDF of Input image(RGB) : [L][3]
	float **CDF_RGB = cal_CDF_RGB(input);	// CDF of Input image(RGB) : [L][3]


	G trans_func_eq_RGB[L][3] = { 0 };		// transfer function

	// histogram equalization on RGB image
	hist_eq_Color(input, equalized_RGB, trans_func_eq_RGB, CDF_RGB);

	// equalized PDF (RGB)
	float** equalized_PDF_RGB = cal_PDF_RGB(equalized_RGB);

	for (int i = 0; i < L; i++) {
		// write PDF
		fprintf(f_PDF_RGB_R, "%d\t%f\n", i, PDF_RGB[i][0]);
		fprintf(f_PDF_RGB_G, "%d\t%f\n", i, PDF_RGB[i][1]);
		fprintf(f_PDF_RGB_B, "%d\t%f\n", i, PDF_RGB[i][2]);
		fprintf(f_equalized_PDF_RGB_R, "%d\t%f\n", i, equalized_PDF_RGB[i][0]);
		fprintf(f_equalized_PDF_RGB_G, "%d\t%f\n", i, equalized_PDF_RGB[i][1]);
		fprintf(f_equalized_PDF_RGB_B, "%d\t%f\n", i, equalized_PDF_RGB[i][2]);

		// write transfer functions
		fprintf(f_trans_func_eq_RGB_R, "%d\t%d\n", i, trans_func_eq_RGB[i][0]);
		fprintf(f_trans_func_eq_RGB_G, "%d\t%d\n", i, trans_func_eq_RGB[i][1]);
		fprintf(f_trans_func_eq_RGB_B, "%d\t%d\n", i, trans_func_eq_RGB[i][2]);
	}

	// memory release
	free(PDF_RGB);
	free(CDF_RGB);
	fclose(f_PDF_RGB_R); fclose(f_PDF_RGB_G); fclose(f_PDF_RGB_B);
	fclose(f_equalized_PDF_RGB_R); fclose(f_equalized_PDF_RGB_G); fclose(f_equalized_PDF_RGB_B);
	fclose(f_trans_func_eq_RGB_R); fclose(f_trans_func_eq_RGB_G); fclose(f_trans_func_eq_RGB_B);

	////////////////////// Show each image ///////////////////////

	namedWindow("RGB", WINDOW_AUTOSIZE);
	imshow("RGB", input);

	namedWindow("Equalized_RGB", WINDOW_AUTOSIZE);
	imshow("Equalized_RGB", equalized_RGB);

	//////////////////////////////////////////////////////////////

	waitKey(0);

	return 0;
}

// histogram equalization on 3 channel image
void hist_eq_Color(Mat &input, Mat &equalized, G(*trans_func)[3], float **CDF) {
//RGB각각에 대하여 trans_func를 적용한다.
	for (int i = 0; i < L; i++) {
		trans_func[i][0] = (G)(L - 1) * CDF[i][0];
		trans_func[i][1] = (G)(L - 1) * CDF[i][1];
		trans_func[i][2] = (G)(L - 1) * CDF[i][2];
	}
//trans_func 값을 바탕으로 imput 행렬을 재정의한다. 3개의 채널을 가지고 있으므로 <Vec3b>로 접근하여 각각의 채널에 접근한다.
	for (int i = 0; i < input.rows; i++) {
		for (int j = 0; j < input.cols; j++) {
			equalized.at<Vec3b>(i, j)[0] = trans_func[input.at<Vec3b>(i, j)[0]][0];
			equalized.at<Vec3b>(i, j)[1] = trans_func[input.at<Vec3b>(i, j)[1]][1];
			equalized.at<Vec3b>(i, j)[2] = trans_func[input.at<Vec3b>(i, j)[2]][2];
		}
	}

}
