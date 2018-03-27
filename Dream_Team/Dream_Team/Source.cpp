#include "geometry.h"
#include "model.h"
#include "tgaimage.h"
#include "Painter.h"
#include <iostream>
#include "Render.h"

const char* dir = "obj/african_head.obj";

const PNGColor white = PNGColor(255, 255, 255, 255);
const PNGColor red = PNGColor(255, 255, 0, 0);
const PNGColor blue = PNGColor(255, 0, 0, 255);
const int width = 800;
const int height = 800;
PNGImage* image = NULL;

int main() {
	
		Model* model=new Model(dir);
		std::cout << "#vert " << model->vertsSize() << " #faces " << model->facesSize() << std::endl;

		image = new PNGImage(width, height, PNGType::RGB);

		model->setScale(width / 2, height / 2);
		//Painter paint(image);
		Render render = Render(image,model);
		render.setCamera(Point3dF(0, 0, 1));
		render.setLight(Point3dF(0, 0, 1));
		render.renderScene();
		//image->flip_vertically();
		image->rotate();
		image->saveImage("output.png");
		/*
	image = PNGImage::openImage("output.png");
	image->saveImage("output1.png");
	*/
	system("pause");
	
	return 0;
}


