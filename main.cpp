#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main()
{
	//��ȡ���ص�һ��ͼƬ����ʾ����
	//imread������ļ�·�����Ը����Լ���ʵ��·���޸ġ�

	//Excese2 RGBת�Ҷ�
	cv::Mat img = imread("C:/Users/STAR ZHANG/Pictures/3.jpg",0);
	imshow("test", img);


	//�ȴ��û�����
	waitKey(0);
	return 0;
}