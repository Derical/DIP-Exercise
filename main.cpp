#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

#define hist_width  400
#define hist_height 400
#define hist_rgb_width  800
#define hist_rgb_height 400

void Calc_histgram(cv::Mat src)
{
	//����ֱ��ͼ����
	float histogram[256][3] = { 0 };
	int height = src.rows;
	int width = src.cols;
	long int size = height * width;

	//����ͼ�� 
	for (int j = 0; j < height; ++j)
	{
		for (int i = 0; i < width; ++i)
		{
			++histogram[src.at<Vec3b>(j, i)[0]][0];
			++histogram[src.at<Vec3b>(j, i)[1]][1];
			++histogram[src.at<Vec3b>(j, i)[2]][2];
		}
	}

	//��һ��
	for (int i = 0; i < 256; ++i)
	{
		histogram[i][0] = histogram[i][0] / size;
		histogram[i][1] = histogram[i][1] / size;
		histogram[i][2] = histogram[i][2] / size;
	}


	//����ֱ��ͼ
	//����������Ϊ400*400
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
	//����ֱ��ͼ����
	float histogram[256][3] = { 0 };
	//����vector��Ϊ����ͨ��������
	std::vector<cv::Mat>	channels;
	cv::split(src, channels);
	//��������ͨ������ֵ
	cv::Mat B = channels.at(0);
	cv::Mat G = channels.at(1);
	cv::Mat R = channels.at(2);
	//*****����*****
	//��ȡ��������
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

	//*****��һ��*****
	/*
	* ����ֱ��ͼ��һ���Ժ��������С��1����Ҫ�Ŵ��Ժ���ʾ��ֱ��
	* ���Ŵ���ٱ�����ʹ���еĻ����������зŴ����߶�
	* ����������������¼��һ��������ֵ�������ֵ�Ŵ�Ϊ�����߶�400
	* ���ֵ�����ɣ�������ֵҲ��Ȼ��������
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
	//����Rͨ��ֱ��ͼ
	Coeficient = (int)(400 / RMax);
	for (int i = 0; i < 256; ++i)
	{
		pt2.y = pt1.y - histogram[i][2] * Coeficient;
		cv::line(dispMat, pt1, pt2, Scalar(0, 0, 255), 1, 8, 0);
		pt2.x = ++pt1.x;
	}
	//����Gͨ��ֱ��ͼ
	Coeficient = (int)(400 / GMax);
	for (int i = 0; i < 256; ++i)
	{
		pt2.y = pt1.y - histogram[i][1] * Coeficient;
		cv::line(dispMat, pt1, pt2, Scalar(0, 255, 0), 1, 8, 0);
		pt2.x = ++pt1.x;
	}
	//����Bͨ��ֱ��ͼ
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
	* Exercise 4��5:
	*		���㲢����ֱ��ͼ
	*/

	cv::Mat src = imread("C:\\Users\\STAR ZHANG\\Pictures\\3.jpg");

	/*
	* ��ʽһ��
	*	��ͨ�������з���
	*	RGB��ͨ��ֱ��ͼ�ֿ���ʾ
	*/

	//Calc_histgram(src);
	
	/*
	* ��ʽ����
	*	ʹ��split��������ͨ����ֵ���ֱ����
	*	RGB��ͨ����ֱ��ͼ��ʾ��һ��Mat��
	*	�Ż���ֱ��ͼ��ʾ
	*/
	Calc_Hisogram(src);

	waitKey(0);
	return 0;
}