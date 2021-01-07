#include <QApplication>

#include "ImageGrid.h"
#include "operatii.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	QWidget window;
	window.setWindowTitle("Proiect PIM-P");
	//window.setFixedSize(1000, 1000);
	//QPushButton* button = new QPushButton("Browse", &window);
	//button->setGeometry(50, 50, 100, 130);

	QString s1 = QFileDialog::getOpenFileName(&window,		// browse image
		"Open a file",										// caption
		"directoryToOpen",									// directory
		"Images (*.png *.jpg)");							// fisiere permise
		
	string imgName = s1.toUtf8().constData();				// convert Qstring to string

	Mat source = imread(imgName, IMREAD_COLOR);				//	read image						

	ImageGrid* grid = new ImageGrid("PIM");				

	//Apply Canny -> gaseste contururile 
	//In functie de threshold (vezi .h) arata mai multe sau mai putine contururi
	Mat edge_map = CannyThreshold(0, 0, source);
	printImage(edge_map, "edge_map.jpg", 0, 0, grid);

	vector<vector<Point>> contours;
	contours = applyContours(contours, edge_map, grid);

	//USING approxPolyDP

	Mat dst(source.size(), CV_8UC3, Scalar::all(0));		//creating a black image with the source's dims						
	vector<Moments> mu(contours.size());					//vector for Moments

	for (int i = 0; i < contours.size(); ++i) {
		mu[i] = moments(contours[i]);
	}

	vector<Point2f> mc(contours.size());

	for (size_t i = 0; i < contours.size(); i++)
	{

		mc[i] = Point2f(static_cast<float>(mu[i].m10 / (mu[i].m00 + 1e-5)),
			static_cast<float>(mu[i].m01 / (mu[i].m00 + 1e-5)));
		cout << "mc[" << i << "]=" << mc[i] << endl;
	}

	Mat drawing2 = Mat::zeros(edge_map.size(), CV_8UC3);
	RNG rng(12345);
	for (size_t i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(drawing2, contours, (int)i, color, 2);
		circle(drawing2, mc[i], 4, color, -1);
	}
	//imshow("ceva ", drawing2);

	// afiseaza Aria si lungimea formelor conturate
	contoursInfo(contours, mu);

	// 
	dst = approximate(dst, contours, mu);
	printImage(dst, "approximare.jpg", 0, 2, grid);

	// eticheteaza formele conturate
	Mat labeled = source.clone();
	labeled = labelShapes(labeled, contours, mu);
	printImage(labeled,"labels.jpg", 1, 0, grid);

	// marcheaza centrul formelor conturate
	dst = findCenters(dst, contours.size(), mu);
	printImage(dst, "center.jpg", 1, 1, grid);

	grid->show();
	//window.show();
	waitKey(0);

	return a.exec();
}
