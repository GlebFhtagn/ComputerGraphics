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

void Render::setCamera(Camera _camera)
{
	camera = _camera;
}

void Render::setCameraPosition(Point3dF position)
{
	camera.setPosition(position);
}

void Render::setCameraDirect(Point3dF direct)
{
	camera.setDirect(direct);
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

float Render::getAngle(Point3dF v1, Point3dF v2)
{
	return ((v1.x*v2.x + v1.y*v2.y + v1.z*v2.z) / (sqrt(v1.x*v1.x + v1.y*v1.y + v1.z*v1.z) * sqrt(v2.x*v2.x + v2.y*v2.y + v2.z*v2.z)));
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
		if (angle <= M_PI/2) {

			
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
							Point3dF tx(polygons_t.at(i).a.x*1024, polygons_t.at(i).b.x * 1024, polygons_t.at(i).c.x * 1024);
							Point3dF ty(polygons_t.at(i).a.y * 1024, polygons_t.at(i).b.y * 1024, polygons_t.at(i).c.y * 1024);
							Point3dF nx(polygons_n.at(i).a.x * 1024, polygons_n.at(i).b.x * 1024, polygons_n.at(i).c.x * 1024);
							Point3dF ny(polygons_n.at(i).a.y * 1024, polygons_n.at(i).b.y * 1024, polygons_n.at(i).c.y * 1024);
							Point3dF nz(polygons_n.at(i).a.z * 1024, polygons_n.at(i).b.z * 1024, polygons_n.at(i).c.z * 1024);
							Point3dF n((nx^barCoord), (ny^barCoord), (nz^barCoord));
							float test_angle = getAngle(n,v);
							PNGColor new_color = model->getColor((tx^barCoord), (ty^barCoord));
							test_angle = abs(test_angle);
							new_color.r *= test_angle;
							new_color.g *= test_angle;
							new_color.b *= test_angle;
								image->setPixel(x + image->get_width() / 2, y + image->get_height() / 2, new_color);					
							//image->setPixel(x+ image->get_width()/2, y + image->get_height() / 2, color*test_angle);
								zBuffer[(y + image->get_height() / 2)*image->get_width() + x + image->get_width() / 2] = z;
						}
					}
				}
			}
		}
	}
}



PNGImage * Render::getImage()
{
	return image;
}


