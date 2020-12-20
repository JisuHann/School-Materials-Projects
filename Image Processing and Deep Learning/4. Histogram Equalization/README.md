# Histogram Equalization  

### Histogram Equalization> GrayScale Image
hist_eq(Mat &input, Mat &equalized, G trans_func, float CDF)
: get trans_func using CDF, and modify intensity value based on trans_func.

### Histogram Equalization> RGB Image
hist_eq_Color(Mat &input, Mat &equalized, G(trans_func)[3], float CDF)
: Modified so that it is assigned to each considering 3 channels while proceeding in the same way as hist_eq.

### Histogram Equalization> YUV
extract Channel Y separately, and hist_eq was applied to perform the same process as grayscale image equalization.

## Details
original_(  ).png : original images
original_PDF_(R/G/B): original PDF Histogram on R,G,B respectively
output_(   ).png : output images (after histogram equalization)
output_PDF_(R/G/B): output PDF Histogram on R,G,B respectively
trans_func_eq_(Y/U/V): transfer function (Histogram equalization function)
