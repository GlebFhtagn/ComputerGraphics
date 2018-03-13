#include "PNGImage.h"


PNGImage::PNGImage(unsigned char _width, unsigned char _height, PNGType type)
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
	int id=i*width*4+j*4;
	data[id] = color.a;
	data[id + 1] = color.r;
	data[id + 2] = color.g;
	data[id + 3] = color.b;
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
	a = 0;
	r = _r;
	g = _g;
	b = _b;
}
