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

	grid->addImage(&image, 0, 0, "cu qimg", 0.0);
	
	

	QImage blurred = gaussBlur(image);
	grid->addImage(&blurred, 0, 1, "gauss blur", 0.0);

	QImage greyScaleImage = makeGreyScale(blurred);
	grid->addImage(&greyScaleImage, 0, 2, "greyscale",0.0 );

	QImage edges;
	edges = edgeDetection(greyScaleImage);
	grid->addImage(&edges, 0, 3, "edges", 0.0);


	QString imageDir = "Images/";
	QString imageFile(imageDir + "giveway.jpg");

//******************************
	int w, h;
	unsigned char* img = Tools::readImageGray8(imageFile, w, h);

	cout << "Image w/h: " << image.width() << "   " << image.height()<<"   "<<image.isGrayscale();

	cout << "\nImage w/h from unsigned char: " << w << "   " << h;

	//for (int i = 0;i < 10;++i) {
		//cout << image.pixelColor() << "  ";
	//}

	unsigned char* negated = negateImage(img, w, h);
	//grid->addImage(negated, w, h, 0, 1, "negativ");
	//grid->addImage(img,w, h, 0, 2, "test");

	

	
	
	
	
	grid->show();
	//Bgrid2->show();
	
	return a.exec();
}

