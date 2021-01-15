#include <QApplication>
#include <QPushButton>

#include "ImageGrid.h"
#include "operatii.h"


int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	a.setStyle("Fusion");

	appTheme();
	a.setPalette(dark_palette);

	Click window;
	window.setGeometry(50, 50, 1700, 860);
	window.show();

	while (imgName.empty()) { waitKey(0); }

	while(imgChg != 0)
	{
		Mat source = imread(imgName, IMREAD_COLOR);						
		
		imgChg = 0;

		//Apply Canny -> gaseste contururile
		//In functie de threshold (vezi .h) arata mai multe sau mai putine contururi
		Mat edge_map = CannyThreshold(0, 0, source);
		printImage(edge_map, "edge_map.jpg");

		vector<vector<Point>> contours;
		contours = applyContours(contours, edge_map);

		vector<Moments> mu(contours.size());					//vector for Moments

		for (int i = 0; i < contours.size(); ++i) {
			mu[i] = moments(contours[i]);
		}

		// afiseaza Aria si lungimea formelor conturate
		contoursInfo(contours, mu);

		// eticheteaza formele conturate
		Mat labeled = source.clone();
		labeled = labelShapes(labeled, contours, mu);
		printImage(labeled, "labels.jpg");
		cropContour(source, edge_map, contours);

		window.show();
		
		while(imgChg == 0)
			waitKey(3000);

		destroyAllWindows();
		imgChg = 1;
	}
	return a.exec();

}