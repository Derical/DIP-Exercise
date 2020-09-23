#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main()
{
	//读取本地的一张图片便显示出来
	//imread后面的文件路径可以根据自己的实际路径修改。

	//Excese 1 :三通道求平均值
	Mat img = imread("C:/Users/STAR ZHANG/Pictures/3.jpg");			//imread(,0) 读取灰度
	int height = img.rows;
	int width = img.cols;
	for (int j = 0; j < height; ++j)
	{
		for (int i = 0; i < width; ++i)
		{
			uchar average = (img.at<Vec3b>(j,i)[0] + img.at<Vec3b>(j,i)[1] + img.at<Vec3b>(j,i)[2])/3;
			img.at<Vec3b>(j, i)[0] = average;
			img.at<Vec3b>(j, i)[1] = average;
			img.at<Vec3b>(j, i)[2] = average;
		}
	}

	imshow("test", img);
	//等待用户按键
	waitKey(0);
	return 0;
}