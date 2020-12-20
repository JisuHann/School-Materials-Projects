Image Rotation Readme

※문제 개요 및 변수
본 문제는 Nearest Neighboor 와 Bilinear Interpolation을 이용하여 이미지 회전을 구현한다.
(input 이미지를 회전하여 output 결과물을 도출)
> output에 해당하는 점 i,j에 배분되는 input의 원 x,y 벡터 값을 위의 보간법을 이용하여 구한다.

※절차
-Nearest Neighboor Interpolation
x,y 주위를 둘러싼 4개의 점 중 이웃하는 점을 고르기 위해 x_gap, y_gap을 이용하여 판단한다.

-Bilinear Interpolation
x,y 주위를 둘러싼 4개의 점 모두 x_gap과 y_gap을 이용하여 반영한다.