#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main()
{
	//��ȡ���ص�һ��ͼƬ����ʾ����
	//imread������ļ�·�����Ը����Լ���ʵ��·���޸ġ�

	//Excese 4
	//ǳ���������
	cv::Mat srcM = imread("C:/Users/STAR ZHANG/Pictures/3.jpg");
	//���
	cv::Mat deepMat = srcM.clone();
	srcM.copyTo(deepMat);
	//ǳ����
	cv::Mat shallowMat = srcM;
	//��ȡͼ��ĸ߶ȺͿ��
	int height = srcM.rows;
	int width = srcM.cols;
	//�������ص�
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			//��������ͨ����ƽ��ֵ
			uchar average = (srcM.at<Vec3b>(j, i)[0] + srcM.at<Vec3b>(j, i)[1] + srcM.at<Vec3b>(j, i)[2]) / 3;
			//�趨��ֵ
			uchar threshold = 100;
			if (average > threshold)
				average = 255;
			else
				average = 0;

			srcM.at<Vec3b>(j, i)[0] = srcM.at<Vec3b>(j, i)[1] = srcM.at<Vec3b>(j, i)[2] = average;
		}
	}
	//���ն��ϴ�ӡÿ�����ص�����ͨ����ֵ
	//������ Ҫ��ӡһ����
	//std::cout << "srcM"			<<srcM << std::endl;
	//std::cout << "deepMat"		<< deepMat << std::endl;
	//std::cout << "shallowMat"   <<shallowMat << std::endl;

	//ֱ����ʾͼƬֱ��һ��
	imshow("srcM", srcM);
	imshow("deepMat", deepMat);
	imshow("shallowMat", shallowMat);

	//��ȻsrcM��shallowMat������ֵ����
	//��deepMat��Ȼ��RGBͼ��
	//ǳ������ֻ��������ͷ����������ʵ���ݣ�������ָ��ָ��ͬһ��λ�ã����Ըı�һ����һ��Ҳ��ı䡣
	//���ָ����ͷ�����ݶ��������ı�һ������һ������䡣	int height = img.rows;


	//�ȴ��û�����
	waitKey(0);
	return 0;
}