#pragma once
#include "geometry.h"


class Camera
{
public:
	Camera();
	Camera(Point3dF _position, Point3dF _direct);
	~Camera();

	void setPosition(Point3dF _position);
	void setDirect(Point3dF _direct);

	Point3dF getPosition();
	Point3dF getDirect();
private:
	Point3dF position;
	Point3dF direct;
};

