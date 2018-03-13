#pragma once
#include <iostream>
#include <vector>

template <class t>struct  Point2d {
	t x;
	t y;
	Point2d() :x(0), y(0) {};
	Point2d(t _x, t _y) : x(_x), y(_y) {};
	friend std::ostream& operator << (std::ostream & output, const Point2d& point) {
		output << point.x << " " << point.y;
		return output;
	}
	friend std::istream& operator >> (std::istream & input, Point2d<t>& point) {
		input >> point.x >> point.y;
		return input;
	}
	friend Point2d<t> operator+(const Point2d<t>& p1, const Point2d<t>& p2) {
		Point2d<t> newPoint(p1.x+p2.x,p1.y+p2.y);
		return newPoint;
	}
	friend Point2d<t> operator*(const Point2d<t>& p1, const Point2d<t>& p2) {
		Point2d<t> newPoint(p1.x * p2.x, p1.y * p2.y);
		return newPoint;
	}
	friend Point2d<t> operator*(const Point2d<t>& p, t a) {
		Point2d<t> newPoint(p.x * a, p.y * a);
		return newPoint;
	}
	friend t & operator^(const Point2d & a, const Point2d & b)
	{
		return (a.x * b.x + a.y * b.y);
	}
};
template <class t>struct Point3d {
	t x;
	t y;
	t z;
	Point3d():x(0),y(0),z(0) {};
	Point3d(t _x, t _y, t _z) : x(_x), y(_y), z(_z) {};
	friend std::ostream& operator << (std::ostream & output, const Point3d& point) {
		output << point.x << " " << point.y << " " << point.z;
		return output;
	}
	friend std::istream& operator >> (std::istream & input, Point3d<t>& point) {
		input >> point.x >> point.y >> point.z;
		return input;
	}

	friend Point3d & operator+(const Point3d & a, const Point3d & b)
	{
		Point3d p(a.x + b.x, a.y + b.y, a.z + b.z);
		return p;
	}

	friend Point3d & operator*(const Point3d & a, const double & b)
	{
		Point3d p(a.x*b, a.y*b, a.z*b);
		return p;
	}

	friend t & operator^(const Point3d & a, const Point3d & b)
	{
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}

	Point2d<t> from3dTo2d() {
		Point2d<t> to2d(x, y);
		return to2d;
	}
};

typedef Point2d<int> Point2dI;
typedef Point2d<float> Point2dF;
typedef Point3d<int> Point3dI;
typedef Point3d<float> Point3dF;

struct Triangle {
	Point3dF a, b, c;
	Triangle():a(0,0,0), b(0,0,0), c(0,0,0) {};
	Triangle(Point3dF _a, Point3dF _b, Point3dF _c) : a(_a.x,_a.y,_a.z), b(_b.x,_b.y,_b.z), c(_c.x,_c.y,_c.z) {};
};