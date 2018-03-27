#include "Render.h"



Render::Render(PNGImage* _image, Model* _model)
{
	image = _image;
	model = _model;
}

Render::~Render()
{
	delete image;
}

void Render::setCamera(Point3dF _v)
{
	v = _v;
}

void Render::setImage(PNGImage * _image)
{
	image = _image;
}

void Render::setModel(Model * _model)
{
	model = _model;
}

void Render::setLight(Point3dF _light)
{
	light = _light;
}


void Render::renderScene()
{
	zBuffer = new float[image->get_width()*image->get_height()];
	float angle, z, intensity;
	memset(zBuffer, 0, sizeof(float));
	std::vector<Triangle> polygons = model->getTrianglesV();
	std::vector<Triangle> polygons_t = model->getTrianglesT();
	Point3dF min, max, barCoord, zero;
	PNGColor color(255,255,255);
	for (int i = 0; i < polygons.size(); i++) {
		angle = acos(polygons.at(i).getAngle(v));
		//intensity = polygons.at(i).getNormal().normalize()^light;
		//std::cout << polygons.at(i).getNormal().getNorm()<<" "<<polygons.at(i).getNormal() <<std::endl;

		if (angle <= 3.14/2) {

			float test_angle = polygons.at(i).getAngle(v);
			max = polygons.at(i).max();
			min = polygons.at(i).min();
		//	PNGColor color(rand() % 256, rand() % 256, rand() % 256);
			for (int x = min.x; x <= max.x; x++)
			{
				for (int y = min.y; y <= max.y; y++)
				{
					barCoord = polygons.at(i).getBarycentricCoordinates(x, y);
					if (barCoord >= zero)
					{
						z = barCoord.x * polygons.at(i).a.z + barCoord.y * polygons.at(i).b.z + barCoord.z * polygons.at(i).c.z;
						if (z > zBuffer[(y + image->get_height() / 2)*image->get_width() + x + image->get_width() / 2]) {
							Point3dF tx(polygons_t.at(i).a.x, polygons_t.at(i).b.x, polygons_t.at(i).c.x);
							Point3dF ty(polygons_t.at(i).a.y, polygons_t.at(i).b.y, polygons_t.at(i).c.y);				
								image->setPixel(x + image->get_width() / 2, y + image->get_height() / 2, model->getColor(tx^barCoord,ty^barCoord));
								zBuffer[(y + image->get_height() / 2)*image->get_width() + x + image->get_width() / 2] = z;
						}
					}

				}
			}
		}
	}
}


