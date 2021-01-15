#pragma once

#include <opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include<opencv2/opencv.hpp>
#include <QPushButton>
#include <QFileDialog>
#include <QPalette>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <windows.h>
#include "ImageGrid.h"

#define LIMIT		810

#define CIRCLE		1
#define TRIANGLE	2
#define SQUARE		3
#define OCTOGON		4
#define NOSHAPE		5


using namespace std;
using namespace cv;
using namespace Qt;

Mat src, src_gray;
Mat dst, detected_edges;
int lowThreshold = 130;
const int max_lowThreshold = 130;
const int ration = 3;
const int kernel_size = 3;

static string imgName;
static int imgChg = 1;
QGridLayout* hbox;
QPalette dark_palette;
QGraphicsView* originalImage;
QGraphicsView* editedImage;
QGraphicsView* signImage;
QTextEdit* textEdit;
QPushButton* uploadImage;
QPushButton* showSteps;
QLabel* label;
QLabel* label_2;
QLabel* label_3;
QLabel* label_4;
QLabel* label_5;

static void selectFile() {
	QWidget window2;

	QString s1 = QFileDialog::getOpenFileName(&window2,		// browse image
		"Open a file",										// caption
		"directoryToOpen",									// directory
		"Images (*.png *.jpg)");							// fisiere permise

	imgName = s1.toUtf8().constData();				// convert Qstring to string
	imgChg = 1;
	cout << imgName << "\t";

	QImage image(QString::fromStdString(imgName));

	if (image.isNull())
	{
		QMessageBox::information(&window2, "Image Viewer", "Error Displaying image");
		return;
	}

	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
	QGraphicsScene* scene = new QGraphicsScene();
	scene->addItem(item);
	originalImage->setScene(scene);

	textEdit->setText("\nRezultat:\n");
}

static void tbdPrint()
{
	ImageGrid* grid = new ImageGrid("Show steps");

	grid->addImage("edge_map.jpg", 0, 0); 
	grid->addImage("contours.jpg", 0, 1);
	grid->addImage("labels.jpg", 0, 2);
	grid->setGeometry(100, 100, 1600, 850);
	grid->show();
}


void printImage(Mat img, string name)
{
	//string path = "C:/Users/Claudiu/Documents/facultate/An 3/PIM-P/ACPI/ACPI/ACPI/" + name;
	imwrite(name, img);
	//grid->addImage(QString::fromStdString(name), x, y, QString::fromStdString(name));
}

class Click : public QWidget {

public:

	Click(QWidget* parent = nullptr) {

		originalImage = new QGraphicsView(this);
		originalImage->setObjectName(QString::fromUtf8("originalImage"));
		originalImage->setGeometry(QRect(30, 80, 550, 700));

		editedImage = new QGraphicsView(this);
		editedImage->setObjectName(QString::fromUtf8("editedImage"));
		editedImage->setGeometry(QRect(700, 80, 550, 700));

		signImage = new QGraphicsView(this);
		signImage->setObjectName(QString::fromUtf8("signImage"));
		signImage->setGeometry(QRect(1340, 80, 300, 300));

		textEdit = new QTextEdit(this);
		textEdit->setObjectName(QString::fromUtf8("textEdit"));
		textEdit->setGeometry(QRect(1340, 500, 300, 230));
		textEdit->setText("Semnul gasit este:");

		uploadImage = new QPushButton(this);
		uploadImage->setObjectName(QString::fromUtf8("uploadImage"));
		uploadImage->setGeometry(QRect(600, 290, 75, 23));

		showSteps = new QPushButton(this);
		showSteps->setObjectName(QString::fromUtf8("showSteps"));
		showSteps->setGeometry(QRect(600, 360, 75, 23));

		label = new QLabel(this);
		label->setObjectName(QString::fromUtf8("label"));
		label->setGeometry(QRect(260, 800, 101, 16));

		label_2 = new QLabel(this);
		label_2->setObjectName(QString::fromUtf8("label_2"));
		label_2->setGeometry(QRect(960, 800, 81, 16));

		label_3 = new QLabel(this);
		label_3->setObjectName(QString::fromUtf8("label_3"));
		label_3->setGeometry(QRect(1470, 480, 61, 16));

		label_4 = new QLabel(this);
		label_4->setObjectName(QString::fromUtf8("label_4"));
		label_4->setGeometry(QRect(955, 50, 80, 16));

		label_5 = new QLabel(this);
		label_5->setObjectName(QString::fromUtf8("label_5"));
		label_5->setGeometry(QRect(1455, 50, 80, 16));

		this->setWindowTitle(QCoreApplication::translate("Widget", "Proiect PI-P", nullptr));
		uploadImage->setText(QCoreApplication::translate("Widget", "Upload image", nullptr));
		showSteps->setText(QCoreApplication::translate("Widget", "Show steps", nullptr));
		label->setText(QCoreApplication::translate("Widget", "Original image", nullptr));
		label_2->setText(QCoreApplication::translate("Widget", "Edited image", nullptr));
		label_3->setText(QCoreApplication::translate("Widget", "Sign found", nullptr));
		label_4->setText(QCoreApplication::translate("Widget", "Sign detection", nullptr));
		label_5->setText(QCoreApplication::translate("Widget", "Sign recognition", nullptr));


		connect(uploadImage, &QPushButton::released, qApp, selectFile);
		connect(showSteps, &QPushButton::released, qApp, tbdPrint);
	
	}
};

void appTheme()
{
	dark_palette = QPalette();
	dark_palette.setColor(QPalette::Window, QColor(53, 53, 53));
	dark_palette.setColor(QPalette::WindowText, Qt::white);
	dark_palette.setColor(QPalette::Base, QColor(35, 35, 35));
	dark_palette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
	dark_palette.setColor(QPalette::ToolTipBase, QColor(25, 25, 25));
	dark_palette.setColor(QPalette::ToolTipText, Qt::white);
	dark_palette.setColor(QPalette::Text, Qt::white);
	dark_palette.setColor(QPalette::Button, QColor(53, 53, 53));
	dark_palette.setColor(QPalette::ButtonText, Qt::white);
	dark_palette.setColor(QPalette::BrightText, Qt::red);
	dark_palette.setColor(QPalette::Link, QColor(42, 130, 218));
	dark_palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
	dark_palette.setColor(QPalette::HighlightedText, QColor(35, 35, 35));
	dark_palette.setColor(QPalette::Active, QPalette::Button, QColor(53, 53, 53));
	dark_palette.setColor(QPalette::Disabled, QPalette::ButtonText, Qt::darkGray);
	dark_palette.setColor(QPalette::Disabled, QPalette::WindowText, Qt::darkGray);
	dark_palette.setColor(QPalette::Disabled, QPalette::Text, Qt::darkGray);
	dark_palette.setColor(QPalette::Disabled, QPalette::Light, QColor(53, 53, 53));
}

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

void setLabel(Mat& img, const string label, vector<cv::Point>& contour)
{
	int font = cv::FONT_HERSHEY_SIMPLEX;
	double scale = 0.4;
	int thickness = 1;
	int base = 0;

	Size text = getTextSize(label, font, scale, thickness, &base);
	Rect rect = boundingRect(contour);

	Point p(rect.x + ((rect.width - text.width) / 2), rect.y + ((rect.height + text.height) / 2));
	rectangle(img, p + Point(0, base), p + Point(text.width, -text.height), CV_RGB(255, 255, 255), FILLED);
	putText(img, label, p, font, scale, CV_RGB(0, 0, 0), thickness, 8);
}


// octagon - Stop
// circle
// triangle
// square
// romb

int* shapeInfo;		//va fi un vector cu marimea = nr de contururi gasite
					//shapeInfo[i] = {1...5} in functie de nr de laturi
					//pentru a nu trece prin toate contururile, doar prin cele ce au sens

int shapeDetector(vector<Point> shape, vector<Point> contour, Mat labeled)
{
	//1 = CERC
	//2 = TRIUNGHI
	//3 = PATRAT / ROMB
	//4 = OCTOGON
	//5 = NIMIC
	int result = 5;

	if (shape.size() == 3)
	{
		cout << " -> triangle";
		setLabel(labeled, "TRI", contour);
		result = 2;
	}

	if (shape.size() == 4)
	{
		cout << " -> square or romb";
		setLabel(labeled, "4Lat", contour);
		result = 3;
	}
	if (shape.size() == 8)
	{
		cout << " -> octagon";
		setLabel(labeled, "OCT", contour);
		result = 4;
	}
	if (shape.size() > 6)
	{
		// Detect and label circles 
		double area = contourArea(contour);
		Rect r = boundingRect(contour);
		int radius = r.width / 2;
		double aria_cerc = (CV_PI * std::pow(radius, 2));

		if (abs(1 - ((double)r.width / r.height)) <= 0.2 &&				// lat = lung
			abs(1 - (area / aria_cerc)) <= 0.2)					     // arie de cerc
		{
			cout << " -> circle";
			setLabel(labeled, "CIR", contour);
			result = 1;
		}
		if (shape.size() == 8)
		{
			int lat = (int)arcLength(contour, true) / 8;
			double aria_cv = contourArea(contour);
			double aria_oct = 2 * (1 + sqrt(2)) * (lat * lat);

			if (abs(1 - (aria_cv / aria_oct)) < abs(1 - (aria_cv / (CV_PI * pow(radius, 2)))))
			{
				
				cout << " -> octagon";
				setLabel(labeled, "OCT", contour);
				result = 4;
			}
		}


	}
	return result;
}

Mat labelShapes(Mat img, vector<vector<Point>> contours, vector<Moments> mu)
{
	cout << "\n\t Shapes info\n";
	vector<vector<Point>> conts_poly(contours.size());

	//variabila declarata global
	shapeInfo = (int*)malloc(contours.size() * sizeof(int));


	for (int i = 0; i < contours.size(); ++i)
	{
		approxPolyDP(Mat(contours[i]), conts_poly[i], (int)arcLength(contours[i], true) * 0.04, true);

		cout << " # i = " << i << "; size = " << conts_poly[i].size();
		//if the Area is greater than LIMIT
		if (fabs(mu[i].m00) > LIMIT)
		{
			//i = nr conturului; in [i] pun 1/2/3/4/5 in functie de ce forma e identificata
			//5 = nicio forma
			shapeInfo[i] = shapeDetector(conts_poly[i], contours[i], img);
		}
		cout << endl;
	}
	return img;
}

void contoursInfo(vector<vector<Point>> contours, vector<Moments> mu)
{
	vector<Point2f> mc(contours.size());

	for (size_t i = 0; i < contours.size(); i++)
	{
		mc[i] = Point2f(static_cast<float>(mu[i].m10 / (mu[i].m00 + 1e-5)),
			static_cast<float>(mu[i].m01 / (mu[i].m00 + 1e-5)));
		cout << "mc[" << i << "]=" << mc[i] << endl;
	}

	cout << "\n\t Info: Arie si Lungime contur \n";

	for (size_t i = 0; i < contours.size(); i++)
	{
		cout << " * Contur[" << i << "] " << fixed << setprecision(2) << 
			" - Arie: " << contourArea(contours[i]) << " - Lungime: " << arcLength(contours[i], true) << endl;
	}
}

vector<vector<Point>> applyContours(vector<vector<Point>> contours, Mat edge_map)
{
	vector<Vec4i> hierarchy;
	Mat drawing = Mat::zeros(edge_map.size(), CV_8UC3);
	RNG rng(12345);

	findContours(edge_map, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	for (size_t i = 0; i < contours.size(); i++)
	{
		if (fabs(contourArea(contours[i])) > LIMIT)
		{
			Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
			drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
		}
	}

	printImage(drawing, "contours.jpg");

	return contours;
}

void reduceColor(const Mat3b& img, Mat3b& rez)
{
	int K = 5;
	int points = img.rows * img.cols;
	Mat data = img.reshape(1, points);

	data.convertTo(data, CV_32F);

	vector<int> colorLabels;
	Mat1f colors;
	kmeans(data, K, colorLabels, cv::TermCriteria(TermCriteria::MAX_ITER, 10, 1.0), 1, cv::KMEANS_PP_CENTERS, colors);

	for (int i = 0; i < points; i++)
	{
		data.at<float>(i, 0) = colors(colorLabels[i], 0);
		data.at<float>(i, 1) = colors(colorLabels[i], 1);
		data.at<float>(i, 2) = colors(colorLabels[i], 2);
	}

	Mat reduced = data.reshape(3, img.rows);
	reduced.convertTo(rez, CV_8U);
}


struct lessVec3b
{
	bool operator()(const Vec3b& lhs, const Vec3b& rhs) const {
		return (lhs[0] != rhs[0]) ? (lhs[0] < rhs[0]) : ((lhs[1] != rhs[1]) ? (lhs[1] < rhs[1]) : (lhs[2] < rhs[2]));
	}
};

map<Vec3b, int, lessVec3b> getColorProcentage(const Mat3b& img)
{
	map<Vec3b, int, lessVec3b> vec_procentage;
	for (int row = 0; row < img.rows; ++row)
	{
		for (int col = 0; col < img.cols; ++col)
		{
			Vec3b color = img(row, col);
			if (vec_procentage.count(color) == 0)
			{
				vec_procentage[color] = 1;
			}
			else
			{
				vec_procentage[color] = vec_procentage[color] + 1;
			}
		}
	}
	return vec_procentage;
}

float redC = 0.0, blueC = 0.0, greenC = 0.0, whiteC = 0.0, blackC = 0.0, yellowC = 0.0;

void cropColors(Mat sent)
{
	Mat3b img = sent.clone();
	Mat3b reduced;

	reduceColor(img, reduced);

	// Get color procentages
	map<Vec3b, int, lessVec3b> palette = getColorProcentage(reduced);

	int area = img.rows * img.cols;
	redC = 0.0, blueC = 0.0, greenC = 0.0, whiteC = 0.0, blackC = 0.0;
	yellowC = 0.0;

	for (auto color : palette)
	{
		float percent = 100.f * float(color.second) / float(area);
		cout << "Color: " << color.first << " \t - Area: " << percent << "%" << endl;

		//verificare daca culoare e rosie
		//daca octetul R e cel putin dublu fata de G si B

		float redd = float(color.first.val[2]);
		float bluee = float(color.first.val[0]);
		float greenn = float(color.first.val[1]);

		//white
		//if (redd > 110 && greenn > 120 && bluee > 130 )
		if (redd > 115 && greenn > 115 && bluee > 115 &&  
			((redd / greenn) > 0.8 && (redd / greenn) < 1.2 ) &&
			((redd / bluee) > 0.8 && (redd / bluee) < 1.2) &&
			((bluee / greenn) > 0.8 && (bluee / greenn) < 1.2 ) )
			whiteC += percent;
		//galben? -> drum cu prioritate
		else if (redd >= 170 && greenn >= 140 && bluee < redd && bluee < greenn)
			yellowC += percent;
		//black
		else if (redd <= 115 && greenn <= 115 && bluee <= 115 &&
			((redd / greenn) > 0.70 && (redd / greenn) < 1.3) &&
			((redd / bluee) > 0.70 && (redd / bluee) < 1.3) &&
			((bluee / greenn) > 0.70 && (bluee / greenn) < 1.3))
			blackC += percent;
		else if (redd >= (bluee * 1.5) - 5 && redd >= (greenn * 1.5) - 5)
			redC += percent;
		else if (greenn >= redd * 1.5 && greenn >= bluee * 1.5)
			greenC += percent;
		else if (bluee >= redd * 1.7 && bluee >= greenn * 1.7)
			blueC += percent;


	}
	cout << "\nRED: " << redC << "\tBLUE: " << blueC << "\tGREEN: " << greenC << endl << "WHITE: " << whiteC << "\tBLACK: " << blackC << "\tYELLOW: " << yellowC << endl;
}

Mat resize64x(Mat img) {

	Mat resized = img.clone();
	resize(resized, resized, cv::Size(64, 64), 0, 0, INTER_LINEAR);
	imshow("64x64", resized);

	return resized;
}

//cercuri

bool isOprireInterzisa() {
	if ((redC >= 25 && redC <= 50) && (blueC >= 15 && blueC <= 30) && whiteC < 9)
		return true;
	return false;
}

bool isAccesInterzis() {
	if (redC >= 55 && whiteC >= 9)
		return true;
	return false;
}

bool isRestrictieViteza() {
	if (redC >= 15 && whiteC >= 15 && blackC >= 5 && blackC <= 30)
		return true;
	return false;
}

bool isPrioritatePtSensInvers() {
	if ((whiteC >= 39.5 && whiteC <= 44.5) && (redC >= 27 && redC <= 32.2) && (blackC >= 1.6 && blackC <= 6.6))
		return true;
	return false;
}

bool isOcolirePrinStanga_Dreapta() {
	if (((whiteC >= 4 && whiteC <= 20) && (blueC >= 30 && blueC <= 80)) || (whiteC <= 5 && blueC >= 50))
		return true;
	return false;
}

bool isObligatoriuDreapta_Stanga() {
	if (((whiteC >= 4 && whiteC <= 20) && (blueC >= 42 && blueC <= 65)) || (whiteC <=5 && blueC >=50))
		return true;
	return false;
}

bool isDepasireaInterzisa() {
	if (redC >= 29 && whiteC >= 30 && blackC < 5)
		return true;
	return false;
}

//triunghi

bool isDrumCuDenivelari() {
	if ((whiteC >= 19 && whiteC <= 30) && (redC >= 17 && redC <= 32) && (blackC >= 2 && blackC <= 10))
		return true;
	return false;
}

bool isCedeazaTrecerea() {
	if ((whiteC >= 17 && whiteC <= 35) && (redC >= 23 && redC <= 55) && blackC <= 2)
		return true;
	return false;
}

bool isCurbaLaDreapta() {
	if ((whiteC >= 23 && whiteC <= 27) && (redC >= 22 && redC <= 26) && (blackC >= 2.5 && blackC <= 7))
		return true;
	return false;
}


//patrulater

bool isSensUnic() {
	if (whiteC >= 8 && blueC >= 65 && blackC < 2 && redC == 0)
		return true;
	return false;
}

bool isTreceredePietoni() {
	if ((whiteC >= 15 && whiteC <= 35) && blueC >= 30)
		return true;
	return false;
}

bool isPrioritateFataDeSensOpus() {
	if ((whiteC <= 10) && blueC >= 65 && redC <= 10 && redC != 0)
		return true;
	return false;
}

bool isDrumCuPrioritate() {
	if (whiteC >= 5 && yellowC >= 10)
		return true;
	return false;
}

bool isSfarsitDrumCuPrioritate() {
	if ((whiteC >= 12 && whiteC <= 30) && (blackC >= 15 && blackC <= 20) && (yellowC >= 15 && yellowC <= 20))
		return true;
	return false;
}



//octogona
bool isStopSign() {
	if (redC >= 53 && whiteC >= 9 && blueC == 0)
		return true;
	return false;
}

bool isAtentionare() {
	if (redC != 0)
		return true;
	return false;
}

bool isInformare() {
	if (blueC != 0)
		return true;
	return false;
}


void addPic(string name)
{
	QImage image(QString::fromStdString(name));
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
	QGraphicsScene* scene = new QGraphicsScene();
	scene->addItem(item);
	signImage->setScene(scene);
}

Mat recogniseSign(Mat rez, vector<Point> contour, int index, int*ok) {

	int ok_rect = 0;
	switch (shapeInfo[index]) {
	case CIRCLE:
		if (isAtentionare()) {
			if (isPrioritatePtSensInvers())
			{
				cout << "\n##### PRIORITATE PENTRU CIRCULATIA DIN SENS INVERS #####\n";
				textEdit->append("\n##### PRIORITATE PENTRU CIRCULATIA DIN SENS INVERS #####\n");
				*ok = 1;
				ok_rect = 1;
			}
			if (isOprireInterzisa())
			{
				cout << "\n##### OPRIREA INTERZISA #####\n";
				textEdit->append("\n##### OPRIREA INTERZISA #####\n");
				addPic("Images/template/oprire interzisa.jpg");
				*ok = 1;
				ok_rect = 1;
			}
			if (isAccesInterzis())
			{
				cout << "\n##### ACCES INTERZIS ####\n";
				textEdit->append("\n##### ACCES INTERZIS ####\n");
				addPic("Images/template/acces interzis.png");
				*ok = 1;
				ok_rect = 1;
			}
			if (isRestrictieViteza())
			{
				cout << "\n##### RESTRICTIE VITEZA #####\n";
				textEdit->append("\n##### RESTRICTIE VITEZA #####\n");
				addPic("Images/template/limitare viteza.jpg");
				*ok = 1;
				ok_rect = 1;
			}
			if (isDepasireaInterzisa())
			{
				cout << "\n##### DEPASIREA INTERZISA #####\n";
				textEdit->append("\n##### DEPASIREA INTERZISA #####\n");
				*ok = 1;
				ok_rect = 1;
			}
		}
		else if (isInformare()) {
			if (isOcolirePrinStanga_Dreapta())
			{
				cout << "\n###### OCOLIRE PRIN STANGA/DREAPTA ######\n";
				textEdit->append("\n###### OCOLIRE PRIN STANGA/DREAPTA ######\n");
				addPic("Images/template/ocolire prin dreapta.jpg");
				*ok = 1;
				ok_rect = 1;
			}
			if (isObligatoriuDreapta_Stanga())
			{
				cout << "\n###### OBLIGATORIU LA STANGA/DREAPTA ######\n";
				textEdit->append("\n###### OBLIGATORIU LA STANGA/DREAPTA ######\n");
				*ok = 1;
				ok_rect = 1;
			}
		}


		break;
	case TRIANGLE:
		if (blackC != 0) {
			if (isCedeazaTrecerea())
			{
				cout << "\n##### CEDEAZA TRECEREA #####\n";
				textEdit->append("\n##### CEDEAZA TRECEREA #####\n");
				addPic("Images/template/cedeaza.jpg");
				*ok = 1;
				ok_rect = 1;
			}
			if (isDrumCuDenivelari())
			{
				cout << "\n##### DRUM CU DENIVELARI #####\n";
				textEdit->append("\n##### DRUM CU DENIVELARI #####\n");
				addPic("Images/template/bumpy ride.png");
				*ok = 1;
				ok_rect = 1;
			}
			if (isCurbaLaDreapta())
			{
				cout << "\n##### CURBA #####\n";
				textEdit->append("\n##### CURBA #####\n");
				*ok = 1;
				ok_rect = 1;
			}
		}

		cout << "\n##### SEMN DE AVERTIZARE #####\n";
		textEdit->append("\n##### SEMN DE AVERTIZARE #####\n");
		if (*ok == 0)
		{
			textEdit->append("  ! ");
			addPic("Images/template/warning sign.jpg");
		}
		*ok = 1;
		ok_rect = 1;

		break;
	case SQUARE:

		if (isSensUnic())
		{
			cout << "\n##### SENS UNIC #####\n";
			textEdit->append("\n##### SENS UNIC #####\n");
			*ok = 1;
			ok_rect = 1;
		}
		if (isTreceredePietoni())
		{
			cout << "\n##### TRECERE DE PIETONI #####\n";
			textEdit->append("\n##### TRECERE DE PIETONI #####\n");
			addPic("Images/template/trecere pietoni.png");
			*ok = 1;
			ok_rect = 1;
		}
		if (isPrioritateFataDeSensOpus())
		{
			cout << "\n##### PRIORITATE FATA DE SENSUL OPUS #####\n";
			textEdit->append("\n##### PRIORITATE FATA DE SENSUL OPUS #####\n");
			*ok = 1;
			ok_rect = 1;
		}
		if (isDrumCuPrioritate())
		{
			cout << "\n##### DRUM CU PRIORITATE #####\n";
			textEdit->append("\n##### DRUM CU PRIORITATE #####\n");
			addPic("Images/template/prioritate.jpg");
			*ok = 1;
			ok_rect = 1;
		}
		else if (isSfarsitDrumCuPrioritate())
		{
			cout << "\n##### SFARSITUL DRUMULUI CU PRIORITATE #####\n";
			textEdit->append("\n##### SFARSITUL DRUMULUI CU PRIORITATE #####\n");
			*ok = 1;
			ok_rect = 1;
		}

		break;
	case OCTOGON:
		if (isStopSign())
		{
			cout << "\n######STOP#####\n";
			textEdit->append("\n######STOP#####\n");
			addPic("Images/template/stop.jpg");
			*ok = 1;
			ok_rect = 1;
		}
		if (isRestrictieViteza())
		{
			cout << "\n##### RESTRICTIE VITEZA #####\n";
			textEdit->append("\n##### RESTRICTIE VITEZA #####\n");
			addPic("Images/template/limitare viteza.jpg");
			*ok = 1;
			ok_rect = 1;
		}

		break;

	case NOSHAPE:
		cout << "\n##### NICIUN SEMN IDENTIFICAT #####\n";
		textEdit->setText("\n##### NICIUN SEMN IDENTIFICAT #####\n");
		break;
	}
	if (ok_rect == 1)
	{
		Rect rect = boundingRect(contour);
		rectangle(rez, rect, Scalar(0, 255, 0), 4, 8, 0);		
	}
	return rez;
}



void cropContour(Mat og, Mat img, vector<vector<Point>> contours)
{
	Mat rez = og.clone();
	string nume = "masca";
	string cropi = "crop";
	int ok = 0;

	for (size_t i = 0; i < contours.size(); i++)
	{
		if (fabs(contourArea(contours[i])) > LIMIT)
		{
			if (shapeInfo[i] != NOSHAPE) {
				Mat masca = Mat::zeros(og.size(), CV_8UC1);
				drawContours(masca, contours, (int)i, 255, -1);
				int index = (int)i;
				string stri = to_string(index);
				string test = nume + stri;
				//imshow(test, masca);

				Mat cropObj(og.size(), CV_8UC3);
				//umple imaginea cu verde
				cropObj = Scalar(0, 255, 0);
				for (int row = 0; row < og.rows; ++row)
				{
					for (int col = 0; col < og.cols; ++col)
					{
						if (masca.at<uchar>(row, col) > 0)
						{
							cropObj.at<Vec3b>(row, col) = og.at<Vec3b>(row, col);
						}
					}
				}
				Rect rect = boundingRect(contours[i]);
				rectangle(cropObj, rect, Scalar(0, 255, 0), 2, 8, 0);
				
				Mat ROI = cropObj(rect);
				//imshow(cropi + stri, cropObj);
				cropi += "micCropat++";
				cout << endl << i << " info: " << shapeInfo[i] << endl;
				cropColors(ROI);
				rez = recogniseSign(rez, contours[i], i, &ok);
				//imshow(cropi + stri + "culoare", ROI);
		
			}
		}
	}
	if (ok == 0)
	{
		cout << "\n##### NICIUN SEMN IDENTIFICAT #####\n";
		textEdit->setText("\n##### NICIUN SEMN IDENTIFICAT #####\n");
	}
	imwrite("rezultat.jpg", rez);

	QImage image(QString::fromStdString("rezultat.jpg"));

	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
	QGraphicsScene* scene = new QGraphicsScene();
	scene->addItem(item);
	editedImage->setScene(scene);
}




