# Filters  
#### 1. Uniform Mean Filter (UnionMeanFilterGray.cpp, UnionMeanFilterRGB.cpp)
Kernel: Average value of Kernel value itself
Output = kernel * Input

#### 2. Gaussian Filter (GaussianFilterGray.cpp, GaussianFilterRGB.cpp)
Kernel: Gaussian value considering the coordinates (x,y) as a whole
Output = kernel * Input

#### 3. Sobel Filter (SobelFilterGray.cpp, SobelFilterRGB.cpp)
Kernel: kernelx, kernely (Sobel Filter value) considering both x extension and y extension
Output = ((x-axis extension value)^2 + (y-axis extension value)^2)^(1/2)

#### 4. Laplacian Filter (LaplacianFilterGray.cpp, LaplacianFilterRGB.cpp)
Kernel: Laplacian Filter value
Output = kernel * Input

#### 5. Gaussian Filter (Seperable) (GaussianFilterSeperableGray.cpp, GaussianFilterRGBSeperable.cpp)
Kernel: kernel and kernel2 using Gaussian considering x and y values respectively
Output = kernel * kernel2 * Input
