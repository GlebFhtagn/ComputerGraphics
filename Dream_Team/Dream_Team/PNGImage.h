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
	PNGImage(std::vector<unsigned char> _data,int _width, int _height, PNGType type);
	~PNGImage();
	static PNGImage* openImage(const char* path);
	void saveImage(const char* path);
	void setPixel(int i, int j, PNGColor color);
	PNGColor getColor(int i, int j);
	int get_width();
	int get_height();
	void rotate();
	std::vector<unsigned char> getData();
private:
	std::vector<unsigned char> data;
	unsigned int width;
	unsigned int heigth;
	void swap_pixels();
	int scaleX;
	int scaleY;
};

