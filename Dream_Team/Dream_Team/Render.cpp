#include "Render.h"



Render::Render(PNGImage * _image, std::vector<std::vector<Point3dF>> _polygons)
{
	image = _image;
	polygons = _polygons;
}

Render::~Render()
{
	delete image;
}
