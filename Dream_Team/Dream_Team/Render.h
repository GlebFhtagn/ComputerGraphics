#pragma once
#include "PNGImage.h"
#include "geometry.h"
#include "model.h"
#define _USE_MATH_DEFINES
#include <cmath>  

class Render
{
public:
	Render(PNGImage* _image, Model* _model);
	~Render();

	void setCamera(Point3dF _v);
	void setImage(PNGImage* _image);
	void setModel(Model* _model);
	void setLight(Point3dF _light);
	void renderScene();

private:
	PNGImage* image;
	Model* model;
	Point3dF v;
	Point3dF light;
	float* zBuffer;
};

