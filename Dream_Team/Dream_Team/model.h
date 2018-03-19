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
	std::vector<Point3dF> vertsN(Point3dI i);
	std::vector<Point3dF> vertsT(Point3dI i);

	std::vector<Triangle> getTrianglesV();
	std::vector<Triangle> getTrianglesN();
	std::vector<Triangle> getTrianglesT();
	void setScale(float _scaleX, float _scaleY);

private:
	std::vector<Point3dF> vertices;
	std::vector<std::vector<Point3dI>> faces;
	std::vector<Point3dF> nvertices;
	std::vector<Point2dF> tvertices;
	float scaleX;
	float scaleY;

	Triangle getTriangleV(int i);
	Triangle getTriangleN(int i);
	Triangle getTriangleT(int i);
};