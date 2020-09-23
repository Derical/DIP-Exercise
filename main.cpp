#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main()
{
	//读取本地的一张图片便显示出来
	//imread后面的文件路径可以根据自己的实际路径修改。

	//Excese 1 :三通道求平均值
	//Mat img = imread("C:/Users/STAR ZHANG/Pictures/3.jpg");
	//int height = img.rows;
	//int width = img.cols;
	//for (int j = 0; j < height; ++j)
	//{
	//	for (int i = 0; i < width; ++i)
	//	{
	//		uchar average = (img.at<Vec3b>(j,i)[0] + img.at<Vec3b>(j,i)[1] + img.at<Vec3b>(j,i)[2])/3;
	//		img.at<Vec3b>(j, i)[0] = average;
	//		img.at<Vec3b>(j, i)[1] = average;
	//		img.at<Vec3b>(j, i)[2] = average;
	//	}
	//}

	//Excese2 RGB转灰度
	//cv::Mat img = imread("C:/Users/STAR ZHANG/Pictures/3.jpg",0);
	//imshow("test", img);

	//Exces3 RGB二值化
	//cv::Mat img = imread("c:/users/star zhang/pictures/3.jpg");
	//int height = img.rows;
	//int width = img.cols;
	//for (int j = 0; j < height; ++j)
	//{
	//	for (int i = 0; i < width; ++i)
	//	{
	//		uchar average = (img.at<Vec3b>(j,i)[0] + img.at<Vec3b>(j,i)[1] + img.at<Vec3b>(j,i)[2])/3;
	//		uchar threshold = 120;				//设定阈值为120
	//											  灰度值大于阈值的像素点会被设置为255即为白色，小于阈值的像素点灰度值会被设置为0即为黑色
	//		if (average > threshold)
	//			average = 255;
	//		else
	//			average = 0;
	//		img.at<Vec3b>(j, i)[0] = average;
	//		img.at<Vec3b>(j, i)[1] = average;
	//		img.at<Vec3b>(j, i)[2] = average;
	//	}
	//}
	//imshow("RGB binaryzation",img);

	//Excese 4
	//浅复制与深复制
	cv::Mat srcM = imread("C:/Users/STAR ZHANG/Pictures/3.jpg");
	//深复制
	cv::Mat deepMat = srcM.clone();
	srcM.copyTo(deepMat);		
	//浅复制
	cv::Mat shallowMat = srcM;
	//获取图像的高度和宽度
	int height = srcM.rows;
	int width = srcM.cols;
	//遍历像素点
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			//计算三个通道的平均值
			uchar average = (srcM.at<Vec3b>(j,i)[0] + srcM.at<Vec3b>(j,i)[1] + srcM.at<Vec3b>(j,i)[2]) / 3;
			//设定阈值
			uchar threshold = 100;
			if (average > threshold)
				average = 255;
			else
				average = 0;

			srcM.at<Vec3b>(j, i)[0] = srcM.at<Vec3b>(j, i)[1] = srcM.at<Vec3b>(j, i)[2] = average;
		}
	}
	//在终端上打印每个像素点三个通道的值
	//打扰了 要打印一万年
	//std::cout << "srcM"			<<srcM << std::endl;
	//std::cout << "deepMat"		<< deepMat << std::endl;
	//std::cout << "shallowMat"   <<shallowMat << std::endl;

	//直接显示图片直观一点
	imshow("srcM",srcM);
	imshow("deepMat",deepMat);
	imshow("shallowMat", shallowMat);

	//显然srcM和shallowMat都被二值化了
	//而deepMat仍然是RGB图像
	//浅拷贝是只拷贝数据头，不拷贝真实数据，即两个指针指向同一个位置，所以改变一个另一个也会改变。
	//深拷贝指数据头和数据都拷贝，改变一个，另一个不会变。

	//等待用户按键
	waitKey(0);
	return 0;
}