#include "media/hist_func.h"
#include <opencv2/imgproc/types_c.h>

void hist_eq(Mat& input, Mat& equalized, G* trans_func, float* CDF);
void hist_match(Mat& input, Mat& result, int* trans_func);
int main() {

	Mat input = imread("C:\\input2.jpg", IMREAD_COLOR);
	Mat equalized_YUV;
	Mat result = input.clone();

	Mat ref = imread("C:\\reference.jpg", IMREAD_COLOR);
	Mat equalized_YUV_ref;

	cvtColor(input, equalized_YUV, CV_RGB2YUV);	// RGB -> YUV
	cvtColor(ref, equalized_YUV_ref, CV_RGB2YUV);

	// split each channel(Y, U, V)
	Mat channels[3];
	split(equalized_YUV, channels);
	Mat Y = channels[0];						// U = channels[1], V = channels[2]

	Mat channels_ref[3];
	split(equalized_YUV_ref, channels_ref);
	Mat Y_ref = channels_ref[0];

	// PDF or transfer function txt files
	FILE* f_equalized_PDF_YUV_R, * f_equalized_PDF_YUV_G, * f_equalized_PDF_YUV_B,* f_PDF_R, * f_PDF_G, * f_PDF_B;
	FILE* f_trans_func_eq_YUV;

	FILE* r_equalized_PDF_YUV, * r_PDF_RGB;
	FILE* r_trans_func_eq_YUV;

	FILE* trans_inverse;

	float** PDF_RGB = cal_PDF_RGB(input);		// PDF of Input image(RGB) : [L][3]
	float* CDF_YUV = cal_CDF(Y);				// CDF of Y channel image

	float** PDF_RGB_ref = cal_PDF_RGB(ref);		// PDF of Input image(RGB) : [L][3]
	float* CDF_YUV_ref = cal_CDF(Y_ref);				// CDF of Y channel image

	fopen_s(&f_PDF_R, "PDF_R.txt", "w+");
	fopen_s(&f_PDF_G, "PDF_G.txt", "w+");
	fopen_s(&f_PDF_B, "PDF_B.txt", "w+");
	fopen_s(&f_equalized_PDF_YUV_R, "equalized_PDF_YUV_R.txt", "w+");
	fopen_s(&f_equalized_PDF_YUV_G, "equalized_PDF_YUV_G.txt", "w+");
	fopen_s(&f_equalized_PDF_YUV_B, "equalized_PDF_YUV_B.txt", "w+");
	fopen_s(&f_trans_func_eq_YUV, "trans_func_eq_YUV.txt", "w+");

	fopen_s(&r_PDF_RGB, "PDF_RGB_ref.txt", "w+");
	fopen_s(&r_equalized_PDF_YUV, "equalized_PDF_YUV_ref.txt", "w+");
	fopen_s(&r_trans_func_eq_YUV, "trans_func_eq_YUV_ref.txt", "w+");
	fopen_s(&trans_inverse, "trans_inverse_hist_match_YUV.txt", "w+");

	G trans_func_eq_YUV[L] = { 0 };			// transfer function
	G trans_func_eq_YUV_ref[L] = { 0 };

	// histogram equalization on Y channel
	hist_eq(Y, Y, trans_func_eq_YUV, CDF_YUV);
	hist_eq(Y_ref, Y_ref, trans_func_eq_YUV_ref, CDF_YUV_ref);

	int trans_inv[L] = { 0 }; //0 Ã¤¿î°Å 
	for (int i = L; i >= 0; i--) {
		trans_inv[trans_func_eq_YUV_ref[i]] = i;
	}

	for (int i = 1; i <=L-1; i++) {
		if (trans_inv[i] == 0) {
			trans_inv[i] = trans_inv[i - 1];
		}
	}

	hist_match(Y, channels[0], trans_inv);

	Mat matching_YUV;
	// merge Y, U, V channels
	merge(channels, 3, matching_YUV);
	merge(channels_ref, 3, equalized_YUV_ref);

	// YUV -> RGB (use "CV_YUV2RGB" flag)
	cvtColor(matching_YUV, matching_YUV, CV_YUV2RGB);

	// equalized PDF (YUV)
	float** matching_PDF_YUV = cal_PDF_RGB(matching_YUV);

	for (int i = 0; i < L; i++) {
		// write PDF
		fprintf(f_PDF_R, "%d\t%f\n", i, PDF_RGB[i][0]);
		fprintf(f_PDF_G, "%d\t%f\n", i, PDF_RGB[i][1]);
		fprintf(f_PDF_B, "%d\t%f\n", i, PDF_RGB[i][2]);
		fprintf(f_equalized_PDF_YUV_R, "%d\t%f\n", i, matching_PDF_YUV[i][0]);
		fprintf(f_equalized_PDF_YUV_G, "%d\t%f\n", i, matching_PDF_YUV[i][1]);
		fprintf(f_equalized_PDF_YUV_B, "%d\t%f\n", i, matching_PDF_YUV[i][2]);
		fprintf(f_trans_func_eq_YUV, "%d\t%d\n", i, trans_func_eq_YUV[i]);
		
		fprintf(r_PDF_RGB, "%d\t%f\t%f\t%f\n", i, PDF_RGB_ref[i][0], PDF_RGB_ref[i][1], PDF_RGB_ref[i][2]);
		fprintf(r_trans_func_eq_YUV, "%d\t%d\n", i, trans_func_eq_YUV_ref[i]);

		fprintf(trans_inverse, "%d\t%d\n", i, trans_inv[i]);
	}

	// memory release
	free(PDF_RGB);
	free(CDF_YUV);
	fclose(f_PDF_R); fclose(f_PDF_G); fclose(f_PDF_B);
	fclose(f_equalized_PDF_YUV_R); fclose(f_equalized_PDF_YUV_G); fclose(f_equalized_PDF_YUV_B);
	fclose(f_trans_func_eq_YUV);

	free(PDF_RGB_ref);
	free(CDF_YUV_ref);
	fclose(r_PDF_RGB);
	fclose(r_equalized_PDF_YUV);
	fclose(r_trans_func_eq_YUV);

	fclose(trans_inverse);

	////////////////////// Show each image ///////////////////////

	namedWindow("Original", WINDOW_AUTOSIZE);
	imshow("Original", input);

	namedWindow("Matching_YUV", WINDOW_AUTOSIZE);
	imshow("Matching_YUV", matching_YUV);

	//////////////////////////////////////////////////////////////

	waitKey(0);

	return 0;
}

// histogram equalization
void hist_eq(Mat& input, Mat& equalized, G* trans_func, float* CDF) {

	// compute transfer function
	for (int i = 0; i < L; i++)
		trans_func[i] = (G)((L - 1) * CDF[i]);

	// perform the transfer function
	for (int i = 0; i < input.rows; i++)
		for (int j = 0; j < input.cols; j++)
			equalized.at<G>(i, j) = trans_func[input.at<G>(i, j)];
}


void hist_match(Mat& input, Mat& result, int* trans_func) {
	for (int i = 0; i < input.rows; i++)
		for (int j = 0; j < input.cols; j++)
			result.at<G>(i, j) = trans_func[input.at<G>(i, j)];
}