#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

#define hist_width  400
#define hist_height 400

void Calc_histgram(cv::Mat src)
{
	//定义直方图矩阵
	float histogram[256][3] = { 0 };
	int height = src.rows;
	int width = src.cols;
	long int size = height * width;

	//遍历图像 
	for (int j = 0; j < height; ++j)
	{
		for (int i = 0; i < width; ++i)
		{
			++histogram[src.at<Vec3b>(j, i)[0]][0];
			++histogram[src.at<Vec3b>(j, i)[1]][1];
			++histogram[src.at<Vec3b>(j, i)[2]][2];
		}
	}

	//归一化
	for (int i = 0; i < 256; ++i)
	{
		histogram[i][0] = histogram[i][0] / size;
		histogram[i][1] = histogram[i][1] / size;
		histogram[i][2] = histogram[i][2] / size;
	}


	//绘制直方图
	//画布的像素为400*400
	cv::Point p1, p2;
	cv::Mat RdispMat(hist_height, hist_width, CV_8UC3, Scalar(0, 0, 0));
	cv::Mat GdispMat(hist_height, hist_width, CV_8UC3, Scalar(0, 0, 0));
	cv::Mat BdispMat(hist_height, hist_width, CV_8UC3, Scalar(0, 0, 0));

	p1.x = p2.x = 10;
	p1.y = 400;

	for (int i = 0; i < 256; ++i)
	{
		p2.y = p1.y - histogram[i][0]*400*20;
		line(RdispMat, p1, p2, CV_RGB(255, 255, 255), 1, 8, 0);
		++p1.x;
		++p2.x;
	}
	p1.x = p2.x = 10;
	p1.y = 400;
	for (int i = 0; i < 256; ++i)
	{
		p2.y = p1.y - histogram[i][1] * 400 * 20;
		line(GdispMat, p1, p2, CV_RGB(255, 255, 255), 1, 8, 0);
		++p1.x;
		++p2.x;
	}
	p1.x = p2.x = 10;
	p1.y = 400;
	for (int i = 0; i < 256; ++i)
	{
		p2.y = p1.y - histogram[i][2] * 400 * 20;
		line(BdispMat, p1, p2, CV_RGB(255, 255, 255), 1, 8, 0);
		++p1.x;
		++p2.x;
	}
	imshow("R", RdispMat);
	imshow("G", GdispMat);
	imshow("B", BdispMat);
}

int main()
{
	/*
	* Exercise 4:
	*		计算直方图
	*/

	cv::Mat src = imread("C:\\Users\\STAR ZHANG\\Pictures\\3.jpg");

	Calc_histgram(src);

	waitKey(0);
	return 0;
}