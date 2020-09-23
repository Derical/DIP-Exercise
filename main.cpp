#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main()
{
	//读取本地的一张图片便显示出来
	//imread后面的文件路径可以根据自己的实际路径修改。

	//Exces3 RGB二值化
	cv::Mat img = imread("c:/users/star zhang/pictures/3.jpg");
	int height = img.rows;
	int width = img.cols;
	for (int j = 0; j < height; ++j)
	{
		for (int i = 0; i < width; ++i)
		{
			uchar average = (img.at<Vec3b>(j,i)[0] + img.at<Vec3b>(j,i)[1] + img.at<Vec3b>(j,i)[2])/3;
			uchar threshold = 120;				//设定阈值为120
												// 灰度值大于阈值的像素点会被设置为255即为白色，小于阈值的像素点灰度值会被设置为0即为黑色
			if (average > threshold)
				average = 255;
			else
				average = 0;
			img.at<Vec3b>(j, i)[0] = average;
			img.at<Vec3b>(j, i)[1] = average;
			img.at<Vec3b>(j, i)[2] = average;
		}
	}
	imshow("RGB binaryzation",img);


	//等待用户按键
	waitKey(0);
	return 0;
}