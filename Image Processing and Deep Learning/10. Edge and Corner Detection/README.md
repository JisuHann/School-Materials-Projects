# Edge and Corner Detection

#### 1. Laplacian of Gaussian
Overview) Apply LoG Filter to lena.jpg.  
- Color Image: LoG_RGB.cpp  
- GrayScale Image: LoG_GrayScale.cpp  
  - Gaussian: Obtain Gaussian result using Mirroring and get_Gaussian_Kernel result matrix,  
  - Laplacian: Get the final LoG result using Mirroring and get_Laplacian_Kernel result matrix.  

#### 2. Canny Edge Detector: Canny.cpp
Overview) Apply Canny function(OpenCV) on lena.jpg.

#### 3. Harris Corner Detector: Harris_corner.cpp
Outline) apply cornerHarris / Non-Maximum Suppression / Subpixel-Refinement to lena.jpg / checkerboard.jpg / checkerboard2.png.  

Non-Maximum Suppression: (radius * radius) 0 and 1 are determined by comparing with surrounding pixels based on the center value based on the window.
