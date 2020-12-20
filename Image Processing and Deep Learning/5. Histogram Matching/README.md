# Histogram Matching

### Histogram Matching> GrayScale Image
#### ※Variable Description
Original Image
  - Mat input> input_gray(grayscale)
  - Mat equalized (matrix with equalization)
  - trans_func_eq[L]: T function of s = T(r)
  - Pointers applied to PDF and CDF: (input) PDF, CDF / (equalized) equalized_PDF
Reference Image
  - Mat ref> ref_gray (grayscale)
  - Mat equalized_ref (matrix with equalization)
  - trans_func_eq_ref[L]: G function of s = G(z)
  - Pointers applied to PDF and CDF: (ref) PDF_ref, CDF_ref /(equalized_ref) equalized_ref_PDF
Output Image
  - Mat result
  - trans_inv: G^(-1)(T(r)) function

#### ※Function description (same as YUV situation)
hist_match(Mat& input, Mat& result, int* trans_func)
: G^(-1) is added to the equalized value from the original image.
G^(-1) function
: After assigning (y,x) values ​​of (x,y) values ​​of G function one by one, replace the non-existing values ​​with surrounding values ​​(i-th side (i+1) or (i-1))

### Histogram Matching> YUV
#### ※Variable Description
Original Image
  - Mat input(RGB)> equalized_YUV(YUV)> Y(channels[0])
  - Mat equalized_YUV (equalization action)
  - trans_func_eq_YUV[L]: T function of s = T(r)
  - Pointers applied to PDF and CDF: (input) PDF_RGB, CDF_YUV / (equalized) equalized_PDF_YUV
Reference Image
  - Mat ref(RGB)> equalized_YUV_ref(YUV)> Y_ref(channels_ref[0])
  - Mat equalized_YUV_ref (equalization action)
  - trans_func_eq_YUV_ref[L]: G function of s = G(z)
  - Pointers applied to PDF and CDF: (ref) PDF_RGB_ref, CDF_YUV_ref /(equalized_ref) equalized_PDF_YUV_ref
Output Image
  - Mat matching_YUV
  - trans_inv: G^(-1)(T(r)) function

## Details
original_(  ).png : original images
original_PDF_(R/G/B): original PDF Histogram on R,G,B respectively
output_(   ).png : output images (after histogram Matching)
output_PDF_(R/G/B): output PDF Histogram on R,G,B respectively
trans_function.txt: transfer function (histogram matching)
