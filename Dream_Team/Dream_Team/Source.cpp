#include "geometry.h"
#include "model.h"
#include "tgaimage.h"
#include "Painter.h"
#include <iostream>

const char* dir = "obj/african_head.obj";

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const int width = 800;
const int height = 800;
TGAImage* image = NULL;

bool exists_test1(const char* name) {
	if (FILE *file = fopen(name, "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}

int main() {

	if (exists_test1(dir)) {
		Model model(dir);
		std::cout << "#vert " << model.vertsSize() << " #faces " << model.facesSize() << std::endl;

		image = new TGAImage(width, height, TGAImage::RGB);
		Painter paint(image);

		for (int i = 0; i < model.facesSize(); i++) {
			paint.polygon(model.verts(model.face(i).at(0)), white, width / 2, height / 2);
		}

		/*Point2dF start(width / 2, height / 2);
		for (int i = 1; i < 18; i++){
			Point2dF end(width / 2 + 200 * cos(i * 2 * 3.14 / 17), height / 2 + 200 * sin(i * 2 * 3.14 / 17));
			paint.lineWu(start,end,white);
		}*/

		image->flip_vertically();
		image->write_tga_file("output.tga");
	}
	else {
		std::cout << "No such file \n";
	}
	system("pause");

	return 0;
}


