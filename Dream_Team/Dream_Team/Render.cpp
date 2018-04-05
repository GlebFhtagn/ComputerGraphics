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
	std::vector<Triangle> polygons_n = model->getTrianglesN();
	Point3dF min, max, barCoord, zero;
	PNGColor color(255,255,255);
	for (int i = 0; i < polygons.size(); i++) {
		angle = acos(polygons.at(i).getAngle(v));
		//intensity = polygons.at(i).getNormal().normalize()^light;
		//std::cout << polygons.at(i).getNormal().getNorm()<<" "<<polygons.at(i).getNormal() <<std::endl;

		if (angle <= 3.14/2) {

			float test_angle = polygons.at(i).getAngle(light);
			Triangle test = polygons.at(i);
			test.a = test.a * 400;
			test.b = test.b * 400;
			test.c = test.c * 400;
			max = test.max();
			min = test.min();

		//	PNGColor color(rand() % 256, rand() % 256, rand() % 256);

			for (int x = min.x; x <= max.x; x++)
			{
				for (int y = min.y; y <= max.y; y++)
				{
					barCoord = test.getBarycentricCoordinates(x, y);
					if (barCoord >= zero)
					{
						z = barCoord.x * test.a.z + barCoord.y * test.b.z + barCoord.z * test.c.z;
						if (z > zBuffer[(y + image->get_height() / 2)*image->get_width() + x + image->get_width() / 2]) {
							Point3dF tx(polygons_t.at(i).a.x*512, polygons_t.at(i).b.x * 512, polygons_t.at(i).c.x * 512);
							Point3dF ty(polygons_t.at(i).a.y * 512, polygons_t.at(i).b.y * 512, polygons_t.at(i).c.y * 512);
								image->setPixel(x + image->get_width() / 2, y + image->get_height() / 2, model->getColor((tx^barCoord)+512,(ty^barCoord)+512));
							Point3dF nx(polygons_n.at(i).a.x * 512, polygons_n.at(i).b.x * 512, polygons_n.at(i).c.x * 512);
							Point3dF ny(polygons_n.at(i).a.y * 512, polygons_n.at(i).b.y * 512, polygons_n.at(i).c.y * 512);
							Point3dF nz(polygons_n.at(i).a.z * 512, polygons_n.at(i).b.z * 512, polygons_n.at(i).c.z * 512);
							
							//image->setPixel(x+ image->get_width()/2, y + image->get_height() / 2, color*test_angle);
								zBuffer[(y + image->get_height() / 2)*image->get_width() + x + image->get_width() / 2] = z;
						}
					}

				}
			}
		}
	}
}


