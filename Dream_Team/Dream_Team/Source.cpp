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

		Model model(dir);
		std::cout << "#vert " << model.vertsSize() << " #faces " << model.facesSize() << std::endl;

		image = new PNGImage(width, height, PNGType::RGB);
		//Painter paint(image);
		Render render = Render(image,model.getTriangles(width/2,height/2));
			//paint.polygon(model.verts(model.face(i).at(0)),red , width / 2, height /2);
			render.Draw_triangle();

		/*Point2dF start(width / 2, height / 2);
		for (int i = 1; i < 18; i++){
			Point2dF end(width / 2 + 200 * cos(i * 2 * 3.14 / 17), height / 2 + 200 * sin(i * 2 * 3.14 / 17));
			paint.lineWu(start,end,white);
		}*/

		//image->flip_vertically();
		image->rotate();
		image->saveImage("output.png");

	system("pause");

	return 0;
}


