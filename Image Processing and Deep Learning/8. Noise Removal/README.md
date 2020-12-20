# Noise Removal

#### 1. Salt and Pepper Noise
Overview) Create an image with salt and pepper noise and remove noise using median filtering
-Add_salt_pepper_Noise
-Salt_pepper_noise_removal: Median Filtering
  -Zero-padding: While applying kernel, set the part outside the value to 0 and save the rest to be applied
  -Mirroring: apply the edge value to the part outside the corner of the corner
  -Adjustkernel: Only the value included in the input was processed, and the Median value was also arbitrarily modified using the num variable.

#### 2. Gaussian Noise_Gaussian Filtering
Outline) Gaussian/Bilateral Filtering is applied using the image with Gaussian Noise.
-Gaussian Filtering: Gaussian.cpp

#### 3. Gaussian Noise_Bilateral Filtering
Outline) Gaussian/Bilateral Filtering is applied using the image with Gaussian Noise.
-Bilateral Filtering: Bilateral.cpp
: Unlike Gaussian Filtering, this creates a kernel in the inside of the for statement reflecting the coordinates one by one.

#### 4. Adaptive Thresholding
Overview) By Adaptive Thresholding, images that have contrast intensity (mostly white and black parts) are more contrasted to shown clearly.
