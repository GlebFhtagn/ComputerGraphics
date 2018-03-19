#pragma once
#include "lodepng.h"
#include <vector>

struct PNGColor
{
	unsigned char a;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	PNGColor();
	PNGColor(unsigned char _a, unsigned char _r, unsigned char _g, unsigned char _b);
	PNGColor(unsigned char _r, unsigned char _g, unsigned char _b);
	friend PNGColor  operator*(const PNGColor & color, const float a);
};
enum PNGType
{
	Greyscale, RGB
};
class PNGImage
{
public:
	PNGImage(int _width, int _height, PNGType type);
	~PNGImage();
	void openImage(const char* path);
	void saveImage(const char* path);
	void setPixel(int i, int j, PNGColor color);
	PNGColor getColor(int i, int j);
	int get_width();
	int get_height();
	void rotate();
private:
	std::vector<unsigned char> data;
	int width;
	int heigth;
	void swap_pixels();
};

