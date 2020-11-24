#include <QApplication>

#include "ImageGrid.h"
#include "operatii.h"

/* Shortcuts:

Scroll wheel - zoom in/out

Left button drag - deplasare in imagine cand aceasta este mai mare decat fereastra

Ctrl+A - activeaza / dezactiveaza ajustarea automata a dimensiunii imaginii 
		 pe care se afla cursorul mouse-ului

Shift+A - activeaza / dezactiveaza ajustarea automata a dimensiunii 
		  tuturor imaginilor

Ctrl+R - reseteaza imaginea curenta la dimensiunile sale initiale

Shift+R - reseteaza toate imaginile la dimensiunile lor initiale

*/

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	
	ImageGrid *grid = new ImageGrid("Prelucrarea imaginilor");

	QString fileName =  "Images/giveway.jpg";

	QImage image;
	
	image.load(fileName);



	QSize sizeImage = image.size();
	int width = sizeImage.width(), height = sizeImage.height();

	//grid->addImage(&image, 0, 0, "cu qimg", 0.0);
	
	

	QImage blurred = gaussBlur(image);
	//grid->addImage(&blurred, 0, 1, "gauss blur", 0.0);

	QImage greyScaleImage = makeGreyScale(blurred);
	//grid->addImage(&greyScaleImage, 0, 2, "greyscale",0.0 );

	QImage edges;
	edges = edgeDetection(greyScaleImage);
	//grid->addImage(&edges, 0, 3, "edges", 0.0);


	QString imageDir = "Images/";
	QString imageFile(imageDir + "giveway.jpg");

//******************************
	int w, h;
	unsigned char* img = Tools::readImageGray8(imageFile, w, h);

	//cout << "Image w/h: " << image.width() << "   " << image.height()<<"   "<<image.isGrayscale();

	//cout << "\nImage w/h from unsigned char: " << w << "   " << h;

	//for (int i = 0;i < 10;++i) {
		//cout << image.pixelColor() << "  ";
	//}

	unsigned char* negated = negateImage(img, w, h);

	//grid->addImage(negated, w, h, 1, 1, "negativ");
	//grid->addImage(img,w, h, 1, 2, "test");

	//cv::Mat imgMat = cv::imread("Images/giveway.jpg", cv::IMREAD_ANYCOLOR);
	
	//unsigned char* imgUCHAR = imgMat.data;
	//grid->addImage(imgUCHAR, imgMat.rows, imgMat.cols, 1, 0, "Uchar din Mat");
	//cv::imshow("cu cv", imgMat);


/********************************************************************/
	src = imread("Images/giveway.jpg", IMREAD_COLOR);
	imshow("color", src);

	dst.create(src.size(), src.type());
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	imshow("greyscale", src_gray);
	namedWindow(window_name, WINDOW_AUTOSIZE);
	CannyThreshold(0, 0);


	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(detected_edges, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	Mat drawing = Mat::zeros(detected_edges.size(), CV_8UC3);
	RNG rng(12345);
	for (size_t i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
	}
	imshow("Contours", drawing);

	QImage test = QImage((uchar*)drawing.data, drawing.cols, drawing.rows, drawing.cols * 3, QImage::Format_RGB888);
	grid->addImage(&test, 0, 1, "Test", 0.0);	
	
	
	
	grid->show();
	//grid2->show();
	
	return a.exec();
}

