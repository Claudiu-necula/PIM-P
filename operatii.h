#pragma once

#include <opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include<opencv2/opencv.hpp>
#include <QPushButton>
#include <QFileDialog>
#include <windows.h>


using namespace std;
using namespace cv;

Mat src, src_gray;
Mat dst, detected_edges;
int lowThreshold = 130;
const int max_lowThreshold = 130;
const int ration = 3;
const int kernel_size = 3;

Mat makeGreyscale(Mat img) {
	Mat result;
	cvtColor(img, result, COLOR_BGR2GRAY);
	return result;
}

static Mat CannyThreshold(int, void*, Mat src)
{
	Mat edges;
	Mat greyscale = makeGreyscale(src);

	blur(greyscale, edges, Size(3, 3));
	Canny(edges, edges, lowThreshold, lowThreshold * ration, kernel_size);
	//imshow("Edge Map", edges);
	return edges;
}

QImage makeGreyScale(QImage img) {
	int width = img.width();
	int height = img.height();
	QImage  greyScaleImage(img.size(), img.format());
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int gray = qGray(img.pixel(i, j));
			greyScaleImage.setPixel(i, j, qRgb(gray, gray, gray));

			//Varianta asta scoate imaginea in nuante de albastru
			//greyScaleImage.setPixel(i, j, qGray(img.pixel(i, j)));
		}
	}

	return greyScaleImage;
}

QImage gaussBlur(QImage img) {
	QImage blur(img.size(), img.format());
	int gaussM[5][5] = { 2, 4, 5, 4, 2,				//gaussian mask
						4, 9, 12, 9, 4,
						5, 12, 15, 12, 5,
						4, 9, 12, 9, 4,
						2, 4, 5, 4, 2 };

	float gaussM_sum = 159.0;				//sum of all gaussM elements

	for (int i = 2; i < img.width() - 2; ++i) {
		for (int j = 2; j < img.height() - 2; ++j) {
			float red = 0, green = 0, blue = 0;

			// *****************************************************
			red =
				gaussM[0][0] * qRed(img.pixel(i - 2, j - 2)) +
				gaussM[0][1] * qRed(img.pixel(i - 1, j - 2)) +
				gaussM[0][2] * qRed(img.pixel(i, j - 2)) +
				gaussM[0][3] * qRed(img.pixel(i + 1, j - 2)) +
				gaussM[0][4] * qRed(img.pixel(i + 2, j - 2)) +

				gaussM[1][0] * qRed(img.pixel(i - 2, j - 1)) +
				gaussM[1][1] * qRed(img.pixel(i - 1, j - 1)) +
				gaussM[1][2] * qRed(img.pixel(i, j - 1)) +
				gaussM[1][3] * qRed(img.pixel(i + 1, j - 1)) +
				gaussM[1][4] * qRed(img.pixel(i + 2, j - 1)) +

				gaussM[2][0] * qRed(img.pixel(i - 2, j)) +
				gaussM[2][1] * qRed(img.pixel(i - 1, j)) +
				gaussM[2][2] * qRed(img.pixel(i, j)) +
				gaussM[2][3] * qRed(img.pixel(i + 1, j)) +
				gaussM[2][4] * qRed(img.pixel(i + 2, j)) +

				gaussM[3][0] * qRed(img.pixel(i - 2, j)) +
				gaussM[3][1] * qRed(img.pixel(i - 1, j)) +
				gaussM[3][2] * qRed(img.pixel(i, j)) +
				gaussM[3][3] * qRed(img.pixel(i + 1, j)) +
				gaussM[3][4] * qRed(img.pixel(i + 2, j)) +

				gaussM[4][0] * qRed(img.pixel(i - 2, j + 1)) +
				gaussM[4][1] * qRed(img.pixel(i - 1, j + 1)) +
				gaussM[4][2] * qRed(img.pixel(i, j + 1)) +
				gaussM[4][3] * qRed(img.pixel(i + 1, j + 1)) +
				gaussM[4][4] * qRed(img.pixel(i + 2, j + 1));



			// *****************************************************
			green =
				gaussM[0][0] * qGreen(img.pixel(i - 2, j - 2)) +
				gaussM[0][1] * qGreen(img.pixel(i - 1, j - 2)) +
				gaussM[0][2] * qGreen(img.pixel(i, j - 2)) +
				gaussM[0][3] * qGreen(img.pixel(i + 1, j - 2)) +
				gaussM[0][4] * qGreen(img.pixel(i + 2, j - 2)) +

				gaussM[1][0] * qGreen(img.pixel(i - 2, j - 1)) +
				gaussM[1][1] * qGreen(img.pixel(i - 1, j - 1)) +
				gaussM[1][2] * qGreen(img.pixel(i, j - 1)) +
				gaussM[1][3] * qGreen(img.pixel(i + 1, j - 1)) +
				gaussM[1][4] * qGreen(img.pixel(i + 2, j - 1)) +

				gaussM[2][0] * qGreen(img.pixel(i - 2, j)) +
				gaussM[2][1] * qGreen(img.pixel(i - 1, j)) +
				gaussM[2][2] * qGreen(img.pixel(i, j)) +
				gaussM[2][3] * qGreen(img.pixel(i + 1, j)) +
				gaussM[2][4] * qGreen(img.pixel(i + 2, j)) +

				gaussM[3][0] * qGreen(img.pixel(i - 2, j)) +
				gaussM[3][1] * qGreen(img.pixel(i - 1, j)) +
				gaussM[3][2] * qGreen(img.pixel(i, j)) +
				gaussM[3][3] * qGreen(img.pixel(i + 1, j)) +
				gaussM[3][4] * qGreen(img.pixel(i + 2, j)) +

				gaussM[4][0] * qGreen(img.pixel(i - 2, j + 1)) +
				gaussM[4][1] * qGreen(img.pixel(i - 1, j + 1)) +
				gaussM[4][2] * qGreen(img.pixel(i, j + 1)) +
				gaussM[4][3] * qGreen(img.pixel(i + 1, j + 1)) +
				gaussM[4][4] * qGreen(img.pixel(i + 2, j + 1));
			// *****************************************************
			blue =
				gaussM[0][0] * qBlue(img.pixel(i - 2, j - 2)) +
				gaussM[0][1] * qBlue(img.pixel(i - 1, j - 2)) +
				gaussM[0][2] * qBlue(img.pixel(i, j - 2)) +
				gaussM[0][3] * qBlue(img.pixel(i + 1, j - 2)) +
				gaussM[0][4] * qBlue(img.pixel(i + 2, j - 2)) +

				gaussM[1][0] * qBlue(img.pixel(i - 2, j - 1)) +
				gaussM[1][1] * qBlue(img.pixel(i - 1, j - 1)) +
				gaussM[1][2] * qBlue(img.pixel(i, j - 1)) +
				gaussM[1][3] * qBlue(img.pixel(i + 1, j - 1)) +
				gaussM[1][4] * qBlue(img.pixel(i + 2, j - 1)) +

				gaussM[2][0] * qBlue(img.pixel(i - 2, j)) +
				gaussM[2][1] * qBlue(img.pixel(i - 1, j)) +
				gaussM[2][2] * qBlue(img.pixel(i, j)) +
				gaussM[2][3] * qBlue(img.pixel(i + 1, j)) +
				gaussM[2][4] * qBlue(img.pixel(i + 2, j)) +

				gaussM[3][0] * qBlue(img.pixel(i - 2, j)) +
				gaussM[3][1] * qBlue(img.pixel(i - 1, j)) +
				gaussM[3][2] * qBlue(img.pixel(i, j)) +
				gaussM[3][3] * qBlue(img.pixel(i + 1, j)) +
				gaussM[3][4] * qBlue(img.pixel(i + 2, j)) +

				gaussM[4][0] * qBlue(img.pixel(i - 2, j + 1)) +
				gaussM[4][1] * qBlue(img.pixel(i - 1, j + 1)) +
				gaussM[4][2] * qBlue(img.pixel(i, j + 1)) +
				gaussM[4][3] * qBlue(img.pixel(i + 1, j + 1)) +
				gaussM[4][4] * qBlue(img.pixel(i + 2, j + 1));

			blur.setPixel(i, j, qRgb(red / gaussM_sum, green / gaussM_sum, blue / gaussM_sum));
		}
	}
	return blur;
}

QImage edgeDetection(QImage img) {

	QImage  edges(img.size(), img.format());

	int coef[3][3] = { -1,-1,-1,
						-1, 8,-1,
						-1,-1,-1 };

	for (int i = 1; i < img.width() - 1; i++)
	{
		for (int j = 1; j < img.height() - 1; j++)
		{
			float v = 0;

			// *****************************************************
			v =
				coef[0][0] * qGray(img.pixel(i + 1, j + 1)) +
				coef[0][1] * qGray(img.pixel(i, j + 1)) +
				coef[0][2] * qGray(img.pixel(i - 1, j + 1)) +

				coef[1][0] * qGray(img.pixel(i + 1, j)) +
				coef[1][1] * qGray(img.pixel(i, j)) +
				coef[1][2] * qGray(img.pixel(i - 1, j)) +

				coef[2][0] * qGray(img.pixel(i + 1, j - 1)) +
				coef[2][1] * qGray(img.pixel(i, j - 1)) +
				coef[2][2] * qGray(img.pixel(i - 1, j - 1));

			edges.setPixel(i, j, qRgb(v, v, v));

		}
	}

	return edges;
}

QImage blurImage(QImage image) {
	QImage blurred(image.size(), image.format());
	int kernel[3][3] = { 1, 2, 1,
						2, 4, 2,
						1, 2, 1 };

	float kernel_sum = 16.0;


	for (int i = 1; i < image.width() - 1; i++)
	{
		for (int j = 1; j < image.height() - 1; j++)
		{
			float red = 0, green = 0, blue = 0;

			// *****************************************************
			red =
				kernel[0][0] * qRed(image.pixel(i + 1, j + 1)) +
				kernel[0][1] * qRed(image.pixel(i, j + 1)) +
				kernel[0][2] * qRed(image.pixel(i - 1, j + 1)) +

				kernel[1][0] * qRed(image.pixel(i + 1, j)) +
				kernel[1][1] * qRed(image.pixel(i, j)) +
				kernel[1][2] * qRed(image.pixel(i - 1, j)) +

				kernel[2][0] * qRed(image.pixel(i + 1, j - 1)) +
				kernel[2][1] * qRed(image.pixel(i, j - 1)) +
				kernel[2][2] * qRed(image.pixel(i - 1, j - 1));

			// *****************************************************
			green =
				kernel[0][0] * qGreen(image.pixel(i + 1, j + 1)) +
				kernel[0][1] * qGreen(image.pixel(i, j + 1)) +
				kernel[0][2] * qGreen(image.pixel(i - 1, j + 1)) +

				kernel[1][0] * qGreen(image.pixel(i + 1, j)) +
				kernel[1][1] * qGreen(image.pixel(i, j)) +
				kernel[1][2] * qGreen(image.pixel(i - 1, j)) +

				kernel[2][0] * qGreen(image.pixel(i + 1, j - 1)) +
				kernel[2][1] * qGreen(image.pixel(i, j - 1)) +
				kernel[2][2] * qGreen(image.pixel(i - 1, j - 1));

			// *****************************************************
			blue =
				kernel[0][0] * qBlue(image.pixel(i + 1, j + 1)) +
				kernel[0][1] * qBlue(image.pixel(i, j + 1)) +
				kernel[0][2] * qBlue(image.pixel(i - 1, j + 1)) +

				kernel[1][0] * qBlue(image.pixel(i + 1, j)) +
				kernel[1][1] * qBlue(image.pixel(i, j)) +
				kernel[1][2] * qBlue(image.pixel(i - 1, j)) +

				kernel[2][0] * qBlue(image.pixel(i + 1, j - 1)) +
				kernel[2][1] * qBlue(image.pixel(i, j - 1)) +
				kernel[2][2] * qBlue(image.pixel(i - 1, j - 1));

			blurred.setPixel(i, j, qRgb(red / kernel_sum, green / kernel_sum, blue / kernel_sum));

		}
	}
	return blurred;
}


unsigned char* negateImage(unsigned char* img, int w, int h)
{
	unsigned char* result = new unsigned char[w * h];		//char = un octet; alocare memorie
	for (int y = 0; y < h; y++)			//parcurgem linie cu linie, nu coloana cu coloana
		for (int x = 0; x < w; x++)
			result[y * w + x] = 255 - img[y * w + x];
	return result;
}

unsigned char* binarizeImage(unsigned char* img, int w, int h)
{
	unsigned char* result = new unsigned char[w * h];		//char = un octet; alocare memorie
	for (int y = 0; y < h; y++)			//parcurgem linie cu linie, nu coloana cu coloana
		for (int x = 0; x < w; x++)
			if (img[y * w + x] > 127)
				result[y * w + x] = 255;
			else
				result[y * w + x] = 0;
	return result;
}

unsigned char* brightenImage(unsigned char* img, int w, int h, int brightness)
{
	unsigned char* result = new unsigned char[w * h];
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			if (img[y * w + x] + brightness > 255)
				result[y * w + x] = 255;
			else if (img[y * w + x] + brightness < 0)
				result[y * w + x] = 0;
			else result[y * w + x] = img[y * w + x] + brightness;
	return result;
}


unsigned char* changeContrast(unsigned char* img, int w, int h, int a, int b)
{
	int sa = a - 20;
	int sb = b + 25;

	int m = sa / a;
	int n = (sb - sa) / (b - a);
	int p = (255 - sb) / (255 - b);

	//cout << "m: " << m << "\tn: " << n << "\tp: " << p;

	unsigned char* result = new unsigned char[w * h];
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++) {

			if (img[y * w + x] < a)
				result[y * w + x] = img[y * w + x] * m;

			if (img[y * w + x] >= a && img[y * w + x] <= b)
				result[y * w + x] = (img[y * w + x] - a) * n + sa;

			if (img[y * w + x] > b && img[y * w + x] <= 255)
				result[y * w + x] = (img[y * w + x] - b) * p + sb;
		}
	return result;
}

unsigned char* gammaCorrection(unsigned char* img, int w, int h)
{
	float s;
	float c = 1;
	float gamma = 2.5;
	unsigned char* result = new unsigned char[w * h];
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
		{
			float temp = (float)img[y * w + x] / 255;
			s = c * pow(temp, gamma);
			result[y * w + x] = (unsigned char)(s * 255);

		}

	return result;
}

unsigned char* bitSlicing(unsigned char* img, int w, int h, int k)
{

	unsigned char* result = new unsigned char[w * h];
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
		{


		}

	return result;
}


unsigned char* contrastComprimation(unsigned char* img, int w, int h, int c)
{

	unsigned char* result = new unsigned char[w * h];

	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
		{
			result[y * w + x] = c * log(1 + img[y * w + x]);

		}

	return result;
}

int* generateHistogram(unsigned char* img, int w, int h) {

	int* concentration = new  int[256];

	for (int i = 0; i <= 255; ++i)
		concentration[i] = 0;

	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			++concentration[img[y * w + x]];

		}
	}
	return concentration;
}


double* histogramEqualization(unsigned char* img, int w, int h) {
	double* result = new double[256];
	int* histogram = generateHistogram(img, w, h);
	for (int i = 0; i < 256; ++i)
		result[i] = (double)histogram[i] / (w * h);

	return result;
}

unsigned char* generateNormImg(unsigned char* img, double* histogram, int w, int h) {

	unsigned char* result = new unsigned char[w * h];

	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			double sum = 0;

			for (int i = 0; i < img[y * w + x]; ++i) {
				sum += histogram[i];
			}
			result[y * w + x] = floor((double)255 * sum);
		}
	}
	return result;

}

unsigned char* blur(unsigned char* img, int w, int h) {

	unsigned char* result = new unsigned char[w * h];

	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			result[y * w + x] = (img[(y * w + x) % (w * h)] + img[((y - 1) * w + x) % (w * h)] + img[((y + 1) * w + x) % (w * h)]
				+ img[(y * w + x - 1) % (w * h)] + img[(y * w + x + 1) % (w * h)]) / 5;
		}
	}
	return result;
}

unsigned char* blurExtensive(unsigned char* img, int w, int h) {

	unsigned char* result = new unsigned char[w * h];

	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			result[y * w + x] = (img[(y * w + x) % (w * h)] + img[((y - 2) * w + x) % (w * h)] + img[((y - 1) * w + x - 1) % (w * h)]
				+ img[((y - 1) * w + x) % (w * h)] + img[((y - 1) * w + x + 1) % (w * h)] + img[(y * w + x - 2) % (w * h)]
				+ img[(y * w + x - 1) % (w * h)] + img[(y * w + x + 1) % (w * h)] + img[(y * w + x + 2) % (w * h)]
				+ img[((y + 1) * w + x - 1) % (w * h)] + img[((y + 1) * w + x) % (w * h)] + img[((y + 1) * w + x + 1) % (w * h)]
				+ img[((y + 2) * w + x) % (w * h)]) / 13;
		}
	}
	return result;
}

unsigned char* motionblur(unsigned char* img, int w, int h) {

	unsigned char* result = new unsigned char[w * h];

	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			result[y * w + x] = (img[(y * w + x) % (w * h)] + img[((y - 4) * w + x - 4) % (w * h)] + img[((y - 3) * w + x - 3) % (w * h)]
				+ img[((y - 2) * w + x - 2) % (w * h)] + img[((y - 1) * w + x - 1) % (w * h)]
				+ img[((y + 4) * w + x + 4) % (w * h)] + img[((y + 3) * w + x + 3) % (w * h)]
				+ img[((y + 2) * w + x + 2) % (w * h)] + img[((y + 1) * w + x + 1) % (w * h)]) / 9;
		}
	}
	return result;
}

unsigned char* arithMedianFilter(unsigned char* img, int w, int h) {
	unsigned char* result = new unsigned char[w * h];

	for (int y = 1; y < h - 1; ++y) {
		for (int x = 1; x < w - 1; ++x) {
			result[(y - 1) * w + x] = (img[(y - 1) * w + x - 1] + img[(y - 1) * w + x] + img[(y - 1) * w + x + 1]
				+ img[y * w + x - 1] + img[y * w + x] + img[y * w + x + 1]
				+ img[(y + 1) * w + x - 1] + img[(y + 1) * w + x] + img[(y + 1) * w + x + 1]) / 9;

		}
	}
	return result;
}

unsigned char* gaussFilter(unsigned char* img, int w, int h) {
	unsigned char* result = new unsigned char[w * h];

	for (int y = 1; y < h - 1; ++y) {
		for (int x = 1; x < w - 1; ++x) {
			result[(y - 1) * w + x] = (img[(y - 1) * w + x - 1] + 2 * img[(y - 1) * w + x] + img[(y - 1) * w + x + 1]
				+ 2 * img[y * w + x - 1] + 4 * img[y * w + x] + 2 * img[y * w + x + 1]
				+ img[(y + 1) * w + x - 1] + 2 * img[(y + 1) * w + x] + img[(y + 1) * w + x + 1]) / 16;

		}
	}
	return result;
}

//LAB 5

unsigned char* medianFilter(unsigned char* img, int w, int h, int m, int n) {
	unsigned char* result = new unsigned char[w * h];
	unsigned char* sorted = new unsigned char[m * n];
	int index;

	for (int y = m; y < h - m; ++y) {
		for (int x = n; x < w - n; ++x) {

			index = 0;
			for (int i = 0; i < m * n; ++i)
				sorted[i] = 0;

			for (int i = 0; i < m; ++i) {
				for (int j = 0; j < n; ++j) {
					sorted[index] = img[(y - m / 2 + i) * w + (x - n / 2 + j)];
					++index;
				}

				std::sort(sorted, sorted + index);
			}

			result[y * w + x] = sorted[index / 2];
		}

	}
	return result;
}

unsigned char* HuangFilter(unsigned char* img, int w, int h, int m, int n) {
	unsigned char* result = new unsigned char[w * h];
	unsigned char* sorted = new unsigned char[m * n];
	int* histogram = 0;
	int index = 0;

	for (int y = m; y < h - m; ++y) {
		for (int x = n; x < w - n; ++x) {
			index = 0;

			for (int i = 0; i < m * n; ++i)
				sorted[i] = 0;

			if (x == 0) {
				for (int i = 0; i < m; ++i) {
					for (int j = 0; j < n; ++j) {
						sorted[index] = img[(y - m / 2 + i) * w + (x - n / 2 + j)];
						++index;
					}
					std::sort(sorted, sorted + index);
				}
				result[y * w + x] = sorted[index / 2];
				histogram = generateHistogram(sorted, m, n);
			}

		}
	}


	return result;

}

void setLabel(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour)
{
	int fontface = cv::FONT_HERSHEY_SIMPLEX;
	double scale = 0.4;
	int thickness = 1;
	int baseline = 0;

	cv::Size text = cv::getTextSize(label, fontface, scale, thickness, &baseline);
	cv::Rect r = cv::boundingRect(contour);

	cv::Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
	cv::rectangle(im, pt + cv::Point(0, baseline), pt + cv::Point(text.width, -text.height), CV_RGB(255, 255, 255), FILLED);
	cv::putText(im, label, pt, fontface, scale, CV_RGB(0, 0, 0), thickness, 8);
}

// octagon - Stop
// circle
// triangle
// square
// romb
void shapeDetector(vector<Point> shape, vector<Point> contour, Mat labeled)
{
	if (shape.size() == 3)
	{
		cout << " -> triangle";
		setLabel(labeled, "TRI", contour) ;
	}

	if (shape.size() == 4)
	{
		cout << " -> square or romb";
		setLabel(labeled, "4Lat", contour);
	}

	if (shape.size() == 8)
	{
		cout << " -> octagon";
		setLabel(labeled, "OCT", contour);
	}

	if (shape.size() > 6)
	{
		// Detect and label circles 
		double area = cv::contourArea(contour);
		cv::Rect r = cv::boundingRect(contour);
		int radius = r.width / 2;

		if (abs(1 - ((double)r.width / r.height)) <= 0.05 &&				// lat = lung
			abs(1 - (area / (CV_PI * std::pow(radius, 2)))) <= 0.05)		// arie de cerc
		{
			cout << " -> circle";
			setLabel(labeled, "CIR", contour);
		}
		else if (shape.size() == 8)
		{
			int lat = (int)arcLength(contour, true) / 8;
			double aria_cv = contourArea(contour);
			double aria_calc = 2 * (1 + sqrt(2)) * (lat * lat);

			if (abs(1 - (aria_cv / aria_calc)) <= 0.15)
			{
				cout << " -> octagon";
				setLabel(labeled, "OCT", contour);
			}
		}

		
	}
}

void printImage(Mat img, string name, int x, int y, ImageGrid* grid)
{
	//string path = "C:/Users/Claudiu/Documents/facultate/An 3/PIM-P/ACPI/ACPI/ACPI/" + name;
	imwrite(name, img);
	grid->addImage(QString::fromStdString(name), x, y, QString::fromStdString(name));
}

Mat findCenters(Mat img, int NrOfContours, vector<Moments> mu)
{
	cout << endl << endl << "Image size: " << img.size() << endl;
	cout << endl << "\tMat(p)" << endl;
	for (int i = 0; i < NrOfContours; ++i)
	{
		if (fabs(mu[i].m00) > 1000)
		{
			Point p(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);

			cout << " # i = " << i << "\b \b" << endl << p << endl;

			circle(img, p, 5, Scalar(128, 0, 0), -1);
		}
	}

	return img;
}

Mat approximate(Mat img, vector<vector<Point>> contours, vector<Moments> mu)
{

	//creating a vector for storing ployline points
	vector<vector<Point>> conts_poly(contours.size());

	for (int i = 0; i < contours.size(); ++i)
	{
		approxPolyDP(Mat(contours[i]), conts_poly[i], (int)arcLength(contours[i], true) * 0.04, true);
		
		//if the Area is greater than 1000 ->?
		if (fabs(mu[i].m00) > 1000)
		{
			drawContours(img, conts_poly, i, Scalar(0, 255, 255), 2, 8);
		}
	}
	return img;
}

Mat labelShapes(Mat img, vector<vector<Point>> contours, vector<Moments> mu)
{
	cout << "\n\t Shapes info\n";
	vector<vector<Point>> conts_poly(contours.size());

	for (int i = 0; i < contours.size(); ++i)
	{
		approxPolyDP(Mat(contours[i]), conts_poly[i], (int)arcLength(contours[i], true) * 0.04, true);

		cout << " # i = " << i << "; size = " << conts_poly[i].size();
		//if the Area is greater than 1000 ->?
		if (fabs(mu[i].m00) > 1000)
		{
			shapeDetector(conts_poly[i], contours[i], img);
		}
		cout << endl;
	}
	return img;
}

void contoursInfo(vector<vector<Point>> contours, vector<Moments> mu)\
{
	cout << "\n\t Info: Area and Contour Length \n";

	for (size_t i = 0; i < contours.size(); i++)
	{
		cout << " * Contour[" << i << "] - Area (M_00) = " << std::fixed << std::setprecision(2) << mu[i].m00
			<< " - Area OpenCV: " << contourArea(contours[i]) << " - Length: " << arcLength(contours[i], true) << endl;
	}
}

vector<vector<Point>> applyContours(vector<vector<Point>> contours, Mat edge_map, ImageGrid* grid)
{
	vector<Vec4i> hierarchy; 
	Mat drawing = Mat::zeros(edge_map.size(), CV_8UC3);
	RNG rng(12345);

	findContours(edge_map, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	//RETR_EXTERNAL, CHAIN_APPROX_SIMPLE

	for (size_t i = 0; i < contours.size(); i++)
	{
		if (fabs(contourArea(contours[i])) > 1000)
		{
			Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
			drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
		}
	}

	printImage(drawing, "contours.jpg", 0, 1, grid);

	return contours;
}
