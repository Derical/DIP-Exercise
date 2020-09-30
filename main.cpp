#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main()
{
	/*
	* Exercise3:
	*		opencv������ͼ����
	*/
	cv::Mat dispMat = imread("C:\\Users\\STAR ZHANG\\Desktop\\histgram.jpg");

	//����Բ��
	cv::Point pt;
	pt.x = 10;
	pt.y = 10;
	circle(dispMat,pt,5,CV_RGB(255,0,0),1,8,0);

	//���߶�
	cv::Point pt1, pt2;
	pt1.x = pt1.y = 10;
	pt2.x = pt2.y = 20;
	line(dispMat,pt1,pt2, CV_RGB(255, 0, 0),1,8,0);

	//�����ο�
	cv::Rect rect;
	rect.x = rect.y = 10;
	rect.height = rect.width = 20;
	rectangle(dispMat,rect,CV_RGB(0,255,0),1,8,0);

	imshow("Output",dispMat);


	waitKey(0);
	return 0;
}