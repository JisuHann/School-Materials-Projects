# Image Stitching

## ※ Problem overview and variables
This problem stitches two images using Affine Transformation and Bilinear Interpolation.


## ※ Variable information
I1: Left image> Change to matrix
Matrix information: l1_row, l1_col
Location: ptl_x, ptl_y
I2: Right image> Change to matrix
Matrix information: l2_row, l2_col
Location: ptr_x, ptr_y (number_of_points)

I_f: Conclusion value
Matrix information: (p1, p2, p3, p4), (p1_, p2_, p3_, p4_)

### Affine Matrix
A12(I1>I2)
A21(I2>I1)


## ※ Steps
1. read each image
2. calculate affine Matrix A12, A21
3. Merge two images
	- compute corners
		: Using A12, A21 information
	- inverse warping with bilinear interpolation
		: set I2 Vector value on I_f
	-blend_stitching
		: Blend I1 and I2(already in I_f) on I_f
