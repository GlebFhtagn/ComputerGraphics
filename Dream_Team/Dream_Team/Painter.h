#pragma once
#include "geometry.h"
#include "tgaimage.h"
#include <cmath>
#include "PNGImage.h"

class Painter
{
public:
	Painter(PNGImage* _image);
	~Painter();
	void line(Point2dF p0, Point2dF p1, PNGColor color);
	void lineB(Point2dF p0, Point2dF p1, PNGColor color);
	void lineWu(Point2dF p0, Point2dF p1, PNGColor color);
	void polygon(std::vector<Point3dF> v, PNGColor color, float scaleX, float scaleY);
private: 
	PNGImage* image;
	Point2dF centre;
};

