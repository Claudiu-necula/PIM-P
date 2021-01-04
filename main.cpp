#include <QApplication>

#include "ImageGrid.h"
#include "operatii.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	ImageGrid *grid = new ImageGrid("Prelucrarea imaginilor");

/********************************************************************/
	//Mat src = imread("Images/stop_sign.jpg", IMREAD_COLOR);
	//imshow("original", src);


	/*
	Mat temp = src.clone();
	cvtColor(temp, temp, COLOR_BGR2RGB);
	QImage initial = QImage((uchar*)temp.data, temp.cols, temp.rows, temp.cols * 3, QImage::Format_RGB888);
	grid->addImage(&initial, 0, 0, "Initial Image", 0.0);
	
	dst.create(src.size(), src.type());
	*/
	//QImage greyscale = QImage((uchar*)src_gray.data, src_gray.cols, src_gray.rows, src_gray.cols * 3, QImage::Format_Grayscale8);
	//grid->addImage(&greyscale, 0, 1, "Greyscale", 0.0);

	//namedWindow("Edge map", WINDOW_AUTOSIZE);
	//CannyThreshold(0, 0);
	//QImage canny = QImage((uchar*)detected_edges.data, detected_edges.cols, detected_edges.rows, detected_edges.cols * 3, QImage::Format_RGB888);
	//grid->addImage(&canny, 1, 0, "Canny", 0.0);

/**************************************************/
	//Load Image
	Mat source = imread("Images/giveway.jpg", IMREAD_COLOR);

	//make greysclae
	Mat greyscale = makeGreyscale(source);

	//Apply Canny -> gaseste contururile 
	//In functie de threshold (vezi .h) arata mai multe sau mai putine contururi
	namedWindow("Edge map", WINDOW_AUTOSIZE);
	Mat edge_map = CannyThreshold(0, 0, source);
	imshow("Edge map", edge_map);

	
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(edge_map, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
	
	Mat drawing = Mat::zeros(edge_map.size(), CV_8UC3);
	RNG rng(12345);
	for (size_t i = 0; i < contours.size(); i++)
	{
		if (contourArea(contours[i]) > 1000) {
			Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
			drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
		}
	}
	imshow("Contours", drawing);


	//USING approxPolyDP

	//creating a black image with the source's dims
	Mat dst(source.size(), CV_8UC3, Scalar::all(0));

	//vector for Moments
	vector<Moments> moms(contours.size());

	for (int i = 0; i < contours.size();++i) {
		moms[i] = moments(contours[i]);
	}

	////creating a vector for storing ployline points
	//vector<vector<Point>> conts_poly(contours.size());
	//for (int i = 0; i < contours.size();++i) {
	//	approxPolyDP(Mat(contours[i]), conts_poly[i], 5, true);
	//	if (conts_poly[i].size() == 3) {
	//		cout << "triunghi" << endl;

	//		drawContours(dst, conts_poly, i, Scalar(0, 255, 255), 2, 8);
	//	}
	//	
	//}
	//imshow("approximare", dst);

	/***********************************************ce*/
	//vector for Moments
	vector<Moments> mu(contours.size());


	for (int i = 0; i < contours.size();++i) {
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
	for (size_t i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(drawing2, contours, (int)i, color, 2);
		circle(drawing2, mc[i], 4, color, -1);
	}
	imshow("Contours", drawing);
	cout << "\t Info: Area and Contour Length \n";
	for (size_t i = 0; i < contours.size(); i++)
	{
		cout << " * Contour[" << i << "] - Area (M_00) = " << std::fixed << std::setprecision(2) << mu[i].m00
			<< " - Area OpenCV: " << contourArea(contours[i]) << " - Length: " << arcLength(contours[i], true) << endl;
	}

	//creating a vector for storing ployline points
	vector<vector<Point>> conts_poly(contours.size());
	for (int i = 0; i < contours.size();++i) {
		approxPolyDP(Mat(contours[i]), conts_poly[i], 5, true);
		//if the Area is greater than 1000 ->?
		if (mu[i].m00 > 1000 ) {
			//cout << "triunghi" << endl;

			drawContours(dst, conts_poly, i, Scalar(0, 255, 255), 2, 8);
			//Point p(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);

			//cout << "Mat(p): " << Mat(p) << endl;


			//circle(dst, p, 5, Scalar(128, 0, 0), -1);
		}

	}
	imshow("approximare", dst);
	
	cout << endl << endl<<"Im size: " << source.size() << endl;
	cout << endl;
	for (int i = 0; i < contours.size();++i) {
		if (mu[i].m00 > 1000) {
			Point p(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);

			cout << "Mat(p): " << Mat(p) << endl;


			circle(dst, p, 5, Scalar(128, 0, 0), -1);
		}
	}
	imshow("Centers", dst);

	

	//shape signature mathcing
	
	
	//grid->show();
	//grid2->show();
	waitKey(0);

	
	return a.exec();
}

