#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main()
{
	//��ȡ���ص�һ��ͼƬ����ʾ����
	//imread������ļ�·�����Ը����Լ���ʵ��·���޸ġ�

	//Excese 1 :��ͨ����ƽ��ֵ
	Mat img = imread("C:/Users/STAR ZHANG/Pictures/3.jpg");			//imread(,0) ��ȡ�Ҷ�
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
	//�ȴ��û�����
	waitKey(0);
	return 0;
}