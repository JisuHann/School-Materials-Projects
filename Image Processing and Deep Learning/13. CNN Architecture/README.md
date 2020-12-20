# CNN Architecture: ResNet, VGGnet

#### resnet50_skeleton.py Overview
class ResNet50_layer4
self.layer1: conv2d + BatchNorm2d + ReLU + MaxPool2d
  - make 3 channels of 32x32 images to 64 channels of 8x8 images
self.layer2: 3 ResidualBlocks
  - make 8x8 image 64 channels to 4x4 image 256 channels
self.layer3: 4 ResidualBlocks
  - make 256 channels of 4x4 images to 512 channels of 2x2 images
self.layer4: 6 ResidualBlocks
  - make 512 channels of 2x2 images to 1024 channels of 2x2 images
self.avgpool
  - 1x1 result in 2x2 image
self.fc: fully connected
  - make 10 channels from 1024 channels
