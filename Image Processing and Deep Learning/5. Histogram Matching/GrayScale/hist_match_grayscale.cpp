#include "media/hist_func.h"
#include <opencv2/imgproc/types_c.h>
#include <array>

void hist_eq(Mat& input, Mat& equalized, G* trans_func, float* CDF);
void hist_match(Mat& input, Mat& result, int* trans_func);

int main() {

	Mat input = imread("C:\\input3.jpg", IMREAD_COLOR);
	Mat ref = imread("C:\\lena.jpg", IMREAD_COLOR);

	Mat input_gray;
	cvtColor(input, input_gray, CV_RGB2GRAY);
	Mat equalized = input_gray.clone();
	Mat result = input_gray.clone();

	Mat ref_gray;
	cvtColor(ref, ref_gray, CV_RGB2GRAY);
	Mat equalized_ref = ref_gray.clone();

	// PDF or transfer function txt files
	FILE* f_equalized_PDF, * f_PDF;
	FILE* f_trans_func_eq;

	FILE* r_equalized_PDF, *r_PDF;
	FILE* r_trans_func_eq;
	FILE* trans_inverse;

	//open txt files using Pointer
	fopen_s(&f_PDF, "PDF.txt", "w+");
	fopen_s(&f_equalized_PDF, "equalized_PDF_gray.txt", "w+");
	fopen_s(&f_trans_func_eq, "trans_func_eq.txt", "w+");

	fopen_s(&r_PDF, "PDF_ref.txt", "w+");
	fopen_s(&r_equalized_PDF, "equalized_PDF_ref.txt", "w+");
	fopen_s(&r_trans_func_eq, "trans_func_eq_ref.txt", "w+");

	fopen_s(&trans_inverse, "match_trans_function.txt", "w+");

	float* PDF = cal_PDF(input_gray);
	float* CDF = cal_CDF(input_gray);

	float* PDF_ref = cal_PDF(ref_gray);
	float* CDF_ref = cal_CDF(ref_gray);

	G trans_func_eq[L] = { 0 };		// transfer function
	G trans_func_eq_ref[L] = { 0 }; //transfer function of reference

	// histogram equalization on RGB image
	//trans_func_eq = T,trans_func_eq_ref(transfer function of Reference) =G
	hist_eq(input_gray, equalized, trans_func_eq, CDF);
	hist_eq(ref_gray, equalized_ref, trans_func_eq_ref, CDF_ref);

	//using trans_func_eq_ref, get G^(-1)
	//먼저 존재하는 x,y값들은 먼저 배치한다.
	int trans_inv[L] = { 0 };
	for (int i = L; i >=0; i--) {
		trans_inv[trans_func_eq_ref[i]] = i;
	}
	//포함되지 않은 x,y 값은 주변값들로 대체한다.
	for (int i =L-2; i >=1; i--) {
		if (trans_inv[i] == 0) {
			trans_inv[i] = trans_inv[i + 1];
		}
	}

	//original image를 넣어 hist_eq로 나온 T(r) 값에 G^(-1) 값을 적용한다.
	//result: final output image
	hist_match(equalized, result, trans_inv);

	// equalized PDF (RGB)
	float* equalized_PDF = cal_PDF(equalized);
	float* equalized_PDF_ref = cal_PDF(equalized_ref);

	for (int i = 0; i < L; i++) {
		// write PDF
		fprintf(f_PDF, "%d\t%f\n", i, PDF[i]);
		fprintf(f_equalized_PDF, "%d\t%f\n", i, equalized_PDF[i]);
		fprintf(f_trans_func_eq, "%d\t%d\n", i, trans_func_eq[i]);

		fprintf(r_PDF, "%d\t%f\n", i, PDF_ref[i]);
		fprintf(r_equalized_PDF, "%d\t%f\n", i, equalized_PDF_ref[i]);
		fprintf(r_trans_func_eq, "%d\t%d\n", i, trans_func_eq_ref[i]);

		fprintf(trans_inverse, "%d\t%d\t%d\t%d\n", i, trans_func_eq_ref[i], trans_inv[i]);
	}


	// memory release
	free(PDF);
	free(CDF);
	fclose(f_PDF);
	fclose(f_equalized_PDF);
	fclose(f_trans_func_eq);

	free(PDF_ref);
	free(CDF_ref);
	fclose(r_PDF);
	fclose(r_equalized_PDF);
	fclose(r_trans_func_eq);
	fclose(trans_inverse);

	////////////////////// Show each image ///////////////////////

	namedWindow("RGB", WINDOW_AUTOSIZE);
	imshow("RGB", input);

	namedWindow("Matching_RGB", WINDOW_AUTOSIZE);
	imshow("Matching_RGB", result);

	//////////////////////////////////////////////////////////////

	waitKey(0);

	return 0;
}

// histogram equalization
void hist_eq(Mat& input, Mat& equalized, G* trans_func, float* CDF) {

	// compute transfer function
	for (int i = 0; i < L; i++) {
		trans_func[i] = (G)((L - 1) * CDF[i]);
	}

	// perform the transfer function
	for (int i = 0; i < input.rows; i++)
		for (int j = 0; j < input.cols; j++)
			equalized.at<G>(i, j) = trans_func[input.at<G>(i, j)];
}

//get G^(-1)(T(r)) result using G^(-1) = trans_func
void hist_match(Mat& input, Mat& result, int *trans_func) {
	for (int i = 0; i < input.rows; i++)
		for (int j = 0; j < input.cols; j++)
			result.at<G>(i, j) = trans_func[input.at<G>(i, j)];
}
