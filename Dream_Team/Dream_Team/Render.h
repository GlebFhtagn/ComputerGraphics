#pragma once
#include "PNGImage.h"
#include "geometry.h"

class Render
{
public:
	Render(PNGImage* _image, std::vector<std::vector<Point3dF>> _polygons);
	~Render();
private:
	PNGImage* image;
	std::vector<std::vector<Point3dF>> polygons;
};

