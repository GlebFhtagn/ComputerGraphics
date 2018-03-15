#pragma once
#include "PNGImage.h"
#include "geometry.h"

class Render
{
public:
	Render(PNGImage* _image, std::vector<Triangle> _polygons);
	~Render();

	void backfaceCulling();
	void withZBuffer();
private:
	PNGImage* image;
	std::vector<Triangle> polygons;

	float* zBuffer;
};

