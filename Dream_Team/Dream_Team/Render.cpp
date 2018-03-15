#include "Render.h"



Render::Render(PNGImage * _image, std::vector<Triangle> _polygons)
{
	image = _image;
	polygons = _polygons;
}

Render::~Render()
{
	delete image;
}

void Render::Draw_triangle()
{	
	for (int i = 0; i < polygons.size(); i++)
	{
		
		//PNGColor color(rand() % 256, rand() % 256, rand() % 256);
		PNGColor color(150,150,0);
		int max_x, min_x, max_y, min_y;
		max_x = max_of_three(polygons.at(i).a.x, polygons.at(i).b.x, polygons.at(i).c.x);
		min_x = min_of_three(polygons.at(i).a.x, polygons.at(i).b.x, polygons.at(i).c.x);
		max_y = max_of_three(polygons.at(i).a.y, polygons.at(i).b.y, polygons.at(i).c.y);
		min_y = min_of_three(polygons.at(i).a.y, polygons.at(i).b.y, polygons.at(i).c.y);
		for (int k = min_x; k <= max_x; k++)
		{
			for (int j = min_y; j <= max_y; j++)
			{
				std::vector<float> bar_coord(3);
				bar_coord = get_barycentric_coordinates(polygons.at(i), k, j);
				if (bar_coord[0] >= 0 && bar_coord[1] >= 0 && bar_coord[2] >= 0)
				{
					image->setPixel(k+image->get_width()/2, j + image->get_height() / 2, color);
				}

			}
		}
	}
}


int Render::max_of_three(int x,int y, int z)
{
	if (x > y && x > z)
	{
		return x;
	}
	else if (y > z)
	{
		return y;
	}
	else
	{
		return z;
	}
}

int Render::min_of_three(int x, int y, int z)
{
	if (x < y && x < z)
	{
		return x;
	}
	else if (y	< z)
	{
		return y;
	}
	else
	{
		return z;
	}
}

std::vector<float> Render::get_barycentric_coordinates(Triangle triangle,int x,int y)
{
	float l;
	float x0 = triangle.a.x;
	float y0 = triangle.a.y;
	float x1 = triangle.b.x;
	float y1 = triangle.b.y;
	float x2 = triangle.c.x;
	float y2 = triangle.c.y;
	std::vector<float> res(3);
	l = ((y - y2)*(x1 - x2) - (x - x2)*(y1 - y2)) / ((y0 - y2)*(x1 - x2) - (x0 - x2)*(y1 - y2));
	res[0] = l;
	l = ((y - y0)*(x2 - x0) - (x - x0)*(y2 - y0)) / ((y1 - y0)*(x2 - x0) - (x1 - x0)*(y2 - y0));
	res[1] = l;
	l = ((y - y1)*(x0 - x1) - (x - x1)*(y0 - y1)) / ((y2 - y1)*(x0 - x1) - (x2 - x1)*(y0 - y1));
	res[2] = l;
	return res;
}
