#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

#define hist_width  400
#define hist_height 400
#define hist_rgb_width  800
#define hist_rgb_height 400

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
	cv::Mat BdispMat(hist_height, hist_width, CV_8UC3, Scalar(0, 0, 0));
	cv::Mat GdispMat(hist_height, hist_width, CV_8UC3, Scalar(0, 0, 0));
	cv::Mat RdispMat(hist_height, hist_width, CV_8UC3, Scalar(0, 0, 0));

	p1.x = p2.x = 10;
	p1.y = 400;

	for (int i = 0; i < 256; ++i)
	{
		p2.y = p1.y - histogram[i][0]*400*20;
		line(BdispMat, p1, p2, CV_RGB(255, 255, 255), 1, 8, 0);
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
		line(RdispMat, p1, p2, CV_RGB(255, 255, 255), 1, 8, 0);
		++p1.x;
		++p2.x;
	}
	imshow("R", RdispMat);
	imshow("G", GdispMat);
	imshow("B", BdispMat);
}

void Calc_Hisogram(cv::Mat src)
{
	//定义直方图矩阵
	float histogram[256][3] = { 0 };
	//定义vector作为三个通道的容器
	std::vector<cv::Mat>	channels;
	cv::split(src, channels);
	//分离三个通道像素值
	cv::Mat B = channels.at(0);
	cv::Mat G = channels.at(1);
	cv::Mat R = channels.at(2);
	//*****遍历*****
	//获取向量长度
	int height = src.rows;
	int width  = src.cols;
	long int size = height * width;
	for (int j = 0; j < height; ++j)
	{
		for (int i = 0; i < width; ++i)
		{
			++histogram[B.at<uchar>(j, i)][0];
			++histogram[G.at<uchar>(j, i)][1];
			++histogram[R.at<uchar>(j, i)][2];
		}
	}

	//*****归一化*****
	/*
	* 由于直方图归一化以后的纵坐标小于1，需要放大以后显示才直观
	* 而放大多少倍才能使现有的画布容纳所有放大后的线段
	* 这里用三个变量记录归一化后最大的值，将最大值放大为画布高度400
	* 最大值能容纳，其他的值也自然能容纳了
	*/
	float BMax = 0;
	float GMax = 0;
	float RMax = 0;
	for (int i = 0; i < 256; ++i)
	{
		histogram[i][0] = histogram[i][0] / size;
		histogram[i][1] = histogram[i][1] / size;
		histogram[i][2] = histogram[i][2] / size;

		if (histogram[i][0] > BMax)
			BMax = histogram[i][0];
		if (histogram[i][1] > GMax)
			GMax = histogram[i][1];
		if (histogram[i][2] > RMax)
			RMax = histogram[i][2];
	}
	cv::Mat dispMat(hist_rgb_height, hist_rgb_width, CV_8UC3, Scalar(0, 0, 0));

	//std::cout << "BMax " << BMax << "\n" << "GMax" << GMax << "\n" << "RMax" << RMax << std::endl;
	cv::Point pt1, pt2;
	pt1.y = 400;
	pt1.x = 0;
	pt2.x = 0;

	int Coeficient = 0;
	//绘制R通道直方图
	Coeficient = (int)(400 / RMax);
	for (int i = 0; i < 256; ++i)
	{
		pt2.y = pt1.y - histogram[i][2] * Coeficient;
		cv::line(dispMat, pt1, pt2, Scalar(0, 0, 255), 1, 8, 0);
		pt2.x = ++pt1.x;
	}
	//绘制G通道直方图
	Coeficient = (int)(400 / GMax);
	for (int i = 0; i < 256; ++i)
	{
		pt2.y = pt1.y - histogram[i][1] * Coeficient;
		cv::line(dispMat, pt1, pt2, Scalar(0, 255, 0), 1, 8, 0);
		pt2.x = ++pt1.x;
	}
	//绘制B通道直方图
	Coeficient = (int)(400 / BMax);
	for (int i = 0; i < 256; ++i)
	{
		pt2.y = pt1.y - histogram[i][0] * Coeficient;
		cv::line(dispMat, pt1, pt2, Scalar(255, 0, 0), 1, 8, 0);
		pt2.x = ++pt1.x;
	}
	imshow("Histogram", dispMat);
}

int main()
{
	/*
	* Exercise 4、5:
	*		计算并绘制直方图
	*/

	cv::Mat src = imread("C:\\Users\\STAR ZHANG\\Pictures\\3.jpg");

	/*
	* 方式一：
	*	三通道不进行分离
	*	RGB三通道直方图分开显示
	*/

	//Calc_histgram(src);
	
	/*
	* 方式二：
	*	使用split分离三个通道的值，分别遍历
	*	RGB三通道的直方图显示在一个Mat里
	*	优化了直方图显示
	*/
	Calc_Hisogram(src);

	waitKey(0);
	return 0;
}