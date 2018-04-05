#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

template <class t>
struct  Point2d {
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
	friend bool operator==(const Point2d & a, const Point2d & b)
	{
		return (a.x == b.x && a.y == b.y);
	}

	friend bool operator!=(const Point2d & a, const Point2d & b)
	{
		return !(a.x == b.x && a.y == b.y);
	}

	float getNorm() {
		return sqrt(pow(x, 2.0) + pow(y, 2.0));
	}
};

template <class t>
struct Point3d {
	t x;
	t y;
	t z;
	Point3d():x(0),y(0),z(0) {};
	Point3d(t _x, t _y, t _z) : x(_x), y(_y), z(_z) {};
	Point3d(Point2d<t> _p) : x(_p.x), y(_p.y), z(0) {};
	friend std::ostream& operator << (std::ostream & output, const Point3d& point) {
		output << point.x << " " << point.y << " " << point.z;
		return output;
	}
	friend std::istream& operator >> (std::istream & input, Point3d<t>& point) {
		input >> point.x >> point.y >> point.z;
		return input;
	}

	friend Point3d  operator+(const Point3d & a, const Point3d & b)
	{
		Point3d p(a.x + b.x, a.y + b.y, a.z + b.z);
		return p;
	}

	friend Point3d  operator*(const Point3d & a, const double & b)
	{
		Point3d p(a.x*b, a.y*b, a.z*b);
		return p;
	}

	friend t  operator^(const Point3d & a, const Point3d & b)
	{
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}

	friend Point3d<t>  operator/(const Point3d & a, const Point3d & b)
	{
		return Point3d(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
	}

	friend bool operator>=(const Point3d & a, const Point3d & b)
	{
		return (a.x >= b.x && a.y >= b.y && a.z >= b.z);
	}

	friend bool operator<(const Point3d & a, const Point3d & b)
	{
		return (a.x >= b.x && a.y >= b.y && a.z >= b.z);
	}

	friend bool operator<=(const Point3d & a, const Point3d & b)
	{
		return (a.x <= b.x && a.y <= b.y && a.z <= b.z);
	}

	friend bool operator>(const Point3d & a, const Point3d & b)
	{
		return !(a.x <= b.x && a.y <= b.y && a.z <= b.z);
	}

	friend Point3d<t> operator-(const Point3d & a, const Point3d & b)
	{
		return Point3d<t>(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	Point3d<float> to2D() {
		return Point3d<float>(x / z, y / z, 1f);
	}

	float getNorm() {
		return sqrt(pow(x,2.0)+ pow(y, 2.0)+ pow(z, 2.0));
	}
	Point3d<float> normalize()
	{
		return Point3d<float>(x / getNorm(), y / getNorm(), z / getNorm());
	}

};

typedef Point2d<int> Point2dI;
typedef Point2d<float> Point2dF;
typedef Point3d<int> Point3dI;
typedef Point3d<float> Point3dF;

struct Triangle {
	Point3dF a, b, c;
	Triangle():a(1,0,0), b(0,1,0), c(0,0,1) {};
	Triangle(Point3dF _a, Point3dF _b, Point3dF _c) : a(_a.x,_a.y,_a.z), b(_b.x,_b.y,_b.z), c(_c.x,_c.y,_c.z) {};

	float getAngle(Point3dF v)
	{
		return (((a - c) / (b - c)) ^ v) / (((a - c) / (b - c)).getNorm()*v.getNorm());
	}

	Point3dF getNormal()
	{
		return (a - c) / (b - c);
	}

	Point3dF getBarycentricCoordinates(float x, float y)
	{
		float x0 = a.x;
		float y0 = a.y;
		float x1 = b.x;
		float y1 = b.y;
		float x2 = c.x;
		float y2 = c.y;
		float l0, l1, l2;
		l0 = ((y - y2)*(x1 - x2) - (x - x2)*(y1 - y2)) / ((y0 - y2)*(x1 - x2) - (x0 - x2)*(y1 - y2));
		l1 = ((y - y0)*(x2 - x0) - (x - x0)*(y2 - y0)) / ((y1 - y0)*(x2 - x0) - (x1 - x0)*(y2 - y0));
		l2 = ((y - y1)*(x0 - x1) - (x - x1)*(y0 - y1)) / ((y2 - y1)*(x0 - x1) - (x2 - x1)*(y0 - y1));
		return Point3dF(l0, l1, l2);
	}
	Point3dF max()
	{
		return Point3dF(std::max(std::max(a.x,b.x),c.x), std::max(std::max(a.y, b.y), c.y), std::max(std::max(a.z, b.z), c.z));
	}
	Point3dF min()
	{
		return Point3dF(std::min(std::min(a.x, b.x), c.x), std::min(std::min(a.y, b.y), c.y), std::min(std::min(a.z, b.z), c.z));
	}
};