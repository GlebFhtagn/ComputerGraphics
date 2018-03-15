#pragma once
#include "PNGImage.h"
#include "geometry.h"

class Render
{
public:
	Render(PNGImage* _image, std::vector<Triangle> _polygons);
	~Render();
	void Draw_triangle(Triangle triangle);
private:
	PNGImage* image;
	std::vector<Triangle> polygons;
	std::vector<float> get_barycentric_coordinates(Triangle triangle,int x,int y);
	int max_of_three(int x,int y,int z);
	int min_of_three(int x, int y, int z);
};

