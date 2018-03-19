#include "PNGImage.h"


PNGImage::PNGImage(int _width, int _height, PNGType type)
{
	width = _width;
	heigth = _height;
	data.resize(heigth*width*4);
}

PNGImage::~PNGImage()
{

}

void PNGImage::openImage(const char * path)
{
	
}



void PNGImage::saveImage(const char * path)
{
	lodepng::State state;
	// input color type
	state.info_raw.colortype = LCT_RGBA;
	state.info_raw.bitdepth = 8;
	// output color type
	state.info_png.color.colortype = LCT_RGBA;
	state.info_png.color.bitdepth = 8;
	state.encoder.auto_convert = 0;
	std::vector<unsigned char> buffer;
	unsigned error = lodepng::encode(buffer, &data[0], width, heigth, state);
	if (!error) lodepng::save_file(buffer, std::string(path));
}

void PNGImage::setPixel(int i, int j, PNGColor color)
{
	if (!((i >= 0 && i < width) && (j >= 0 && j < heigth))) return;
	//int id = i*heigth * 4 + j * 4;
	int id= (heigth - j - 1)*heigth* 4 + i * 4;
	data[id] = color.r;
	data[id + 1] = color.g;
	data[id + 2] = color.b;
	data[id + 3] = color.a;
}

PNGColor PNGImage::getColor(int i, int j)
{
	return PNGColor();
}

int PNGImage::get_width()
{
	return width;
}

int PNGImage::get_height()
{
	return heigth;
}

void PNGImage::rotate()
{
	//swap_pixels();
}

void PNGImage::swap_pixels()
{
	std::vector<unsigned char> vec_buff(heigth*width*4);
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < heigth ; j++)
		{
			int id1 = i*width * 4 + j * 4;
			int id2 = (heigth-j-1)*heigth * 4 + i * 4;
			vec_buff[id2] = data[id1];
			vec_buff[id2+1] = data[id1+1];
			vec_buff[id2+2] = data[id1+2];
			vec_buff[id2+3] = data[id1+3];
		}
	}
	data = vec_buff;
}

PNGColor::PNGColor()
{
	a = 0;
	r = 0;
	g = 0;
	b = 0;
}

PNGColor::PNGColor(unsigned char _a, unsigned char _r, unsigned char _g, unsigned char _b)
{
	a = _a;
	r = _r;
	g = _g;
	b = _b;
}

PNGColor::PNGColor(unsigned char _r, unsigned char _g, unsigned char _b)
{
	a = 255;
	r = _r;
	g = _g;
	b = _b;
}

PNGColor  operator*(const PNGColor & color, const float a)
{
	return PNGColor(color.a * a,color.r,color.g,color.b);
}
