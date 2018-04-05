#include "Camera.h"



Camera::Camera()
{
	position = Point3dF(0, 0, -1);
	direct = Point3dF(0, 0, 1);
}

Camera::Camera(Point3dF _position, Point3dF _direct)
{
	position = _position;
	direct = _direct;
}


Camera::~Camera()
{

}

void Camera::setPosition(Point3dF _position)
{
	position = _position;
}

void Camera::setDirect(Point3dF _direct)
{
	direct = _direct;
}

Point3dF Camera::getPosition()
{
	return Point3dF(position);
}

Point3dF Camera::getDirect()
{
	return Point3dF(direct);
}
