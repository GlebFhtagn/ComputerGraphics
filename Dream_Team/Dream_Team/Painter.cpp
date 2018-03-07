#include "Painter.h"

Painter::Painter(TGAImage * _image)
{
	image = _image;
	centre.x = _image->get_width()/2;
	centre.y = _image->get_height()/2;
}

Painter::~Painter()
{

}

void Painter::line(Point2dF p0, Point2dF p1, TGAColor color)
{
	for (float t = 0.; t<1.; t += .05) {
		int x = p0.x*(1. - t) + p1.x*t;
		int y = p0.y*(1. - t) + p1.y*t;
		image->set(x, y, color);
	}
}

void Painter::lineB(Point2dF p0, Point2dF p1, TGAColor color)
{
	bool steep = false;
	if (std::abs(p0.x - p1.x)<std::abs(p0.y - p1.y)) {
		std::swap(p0.x, p0.y);
		std::swap(p1.x, p1.y);
		steep = true;
	}
	if (p0.x>p1.x) {
		std::swap(p0.x, p1.x);
		std::swap(p0.y, p1.y);
	}
	int dx = p1.x - p0.x;
	int dy = p1.y - p0.y;
	float derror = std::abs(dy / float(dx));
	float error = 0;
	int y = p0.y;

	for (int x = p0.x; x <= p1.x; x++) {
		if (!steep) {
			image->set(x, y, color);
		}
		else {
			image->set(y, x, color);
		}
		error += derror;
		if (error > .5) {
			y += (p1.y > p0.y ? 1 : -1);
			error -= 1.;
		}
	}
}

void Painter::lineWu(Point2dF p0, Point2dF p1, TGAColor color)
{
	bool steep = false;
	if (std::abs(p0.x - p1.x)<std::abs(p0.y - p1.y)) {
		std::swap(p0.x, p0.y);
		std::swap(p1.x, p1.y);
		steep = true;
	}
	if (p0.x>p1.x) {
		std::swap(p0.x, p1.x);
		std::swap(p0.y, p1.y);
	}
	int dx = p1.x - p0.x;
	int dy = p1.y - p0.y;
	float derror = std::abs(dy / float(dx));
	float error = 0;
	int y = p0.y;
	int sy = (p1.y > p0.y ? 1 : -1);
	for (int x = p0.x; x <= p1.x; x++) {
		if (!steep) {
			image->set(x, y, TGAColor(255 * (1 - error), 255 * (1 - error), 255 * (1 - error), 255 * (1 - error)));
			image->set(x, y + sy, TGAColor(255 * error, 255 * error, 255 * error, 255 * error));
		}
		else {
			image->set(y, x, TGAColor(255 * (1 - error), 255 * (1 - error), 255 * (1 - error), 255 * (1 - error)));
			image->set(y + sy, x, TGAColor(255 * error, 255 * error, 255 * error, 255 * error));
		}
		error += derror;
		if (error > 1.0) {
			y += sy;
			error -= 1.;
		}
	}
}

void Painter::polygon(std::vector<Point3dF> v, TGAColor color, float scaleX, float scaleY)
{
	for (int i = 0; i < v.size(); i++) {
		lineWu((v.at(i).from3dTo2d()*scaleX)+centre, (v.at((i+1)%v.size()).from3dTo2d()*scaleY)+centre, color);
	}
}
