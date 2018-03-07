#pragma once
#include "geometry.h"
#include "tgaimage.h"
#include <cmath>

class Painter
{
public:
	Painter(TGAImage* _image);
	~Painter();
	void line(Point2dF p0, Point2dF p1, TGAColor color);
	void lineB(Point2dF p0, Point2dF p1, TGAColor color);
	void lineWu(Point2dF p0, Point2dF p1, TGAColor color);
	void polygon(std::vector<Point3dF> v, TGAColor color, float scaleX, float scaleY);
private: 
	TGAImage* image;
	Point2dF centre;
};

