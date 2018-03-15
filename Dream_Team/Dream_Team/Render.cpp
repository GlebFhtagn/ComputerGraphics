#include "Render.h"



Render::Render(PNGImage * _image, std::vector<Triangle> _polygons)
{
	image = _image;
	polygons = _polygons;
}

Render::~Render()
{
	delete image;
}

void Render::backfaceCulling()
{
}

void Render::withZBuffer()
{
}
