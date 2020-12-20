#Histogram Stretching

linear_stretching(Mat &input, Mat &stretched, G trans_func, G x1, G x2, G y1, G y2)
: After specifying the range through cal_PDF, the section intensity is corrected by obtaining the slope and the y-intercept (based on the received interval (x1, y1) and (x2, y2) values)
