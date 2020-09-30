#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main()
{
	/*
	* Exercise 1
	*		:RGB三通道分离
	*/
	cv::Mat src_color = imread("C:/Users/STAR ZHANG/Pictures/4.png");
	std::vector<cv::Mat> channels;
	cv::split(src_color, channels);
	cv::Mat B = channels.at(0);
	cv::Mat G = channels.at(1);
	cv::Mat R = channels.at(2);
	cv::imshow("red", R);
	cv::imshow("blue", B);
	cv::imshow("green", G);
	cv::imshow("original Mat", src_color);
	//等待用户按键
	waitKey(0);

	return 0;
}