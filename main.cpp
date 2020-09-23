#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main()
{
	//��ȡ���ص�һ��ͼƬ����ʾ����
	//imread������ļ�·�����Ը����Լ���ʵ��·���޸ġ�

	//Exces3 RGB��ֵ��
	cv::Mat img = imread("c:/users/star zhang/pictures/3.jpg");
	int height = img.rows;
	int width = img.cols;
	for (int j = 0; j < height; ++j)
	{
		for (int i = 0; i < width; ++i)
		{
			uchar average = (img.at<Vec3b>(j,i)[0] + img.at<Vec3b>(j,i)[1] + img.at<Vec3b>(j,i)[2])/3;
			uchar threshold = 120;				//�趨��ֵΪ120
												// �Ҷ�ֵ������ֵ�����ص�ᱻ����Ϊ255��Ϊ��ɫ��С����ֵ�����ص�Ҷ�ֵ�ᱻ����Ϊ0��Ϊ��ɫ
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


	//�ȴ��û�����
	waitKey(0);
	return 0;
}