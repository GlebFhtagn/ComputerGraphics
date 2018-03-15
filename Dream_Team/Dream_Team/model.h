#pragma once
#include <vector>
#include "geometry.h"
class Model {
public:
	Model(const char* path);
	int vertsSize();
	int facesSize();
	int nvertSize();
	int tvertSize();
	std::vector<Point3dI> face(int i);
	std::vector<Point3dF> verts(Point3dI i);
	Triangle getTriangle(int i, float scaleX, float scaleY);
	std::vector<Triangle> getTriangles(float scaleX, float scaleY);

private:
	std::vector<Point3dF> vertices;
	std::vector<std::vector<Point3dI>> faces;
	std::vector<Point3dF> nvertices;
	std::vector<Point2dF> tvertices;
};