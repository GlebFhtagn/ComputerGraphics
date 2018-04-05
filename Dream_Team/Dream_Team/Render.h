#pragma once
#define _USE_MATH_DEFINES
#include "PNGImage.h"
#include "geometry.h"
#include "model.h"
#include "Camera.h"
#include <cmath>  

class Render
{
public:
	Render(PNGImage* _image, Model* _model);
	~Render();

	void setCamera(Point3dF _v);
	void setCamera(Camera _camera);
	void setCameraPosition(Point3dF position);
	void setCameraDirect(Point3dF direct);
	void setImage(PNGImage* _image);
	void setModel(Model* _model);
	void setLight(Point3dF _light);
	void renderScene();
	PNGImage* getImage();

private:
	PNGImage* image;
	Model* model;
	Point3dF v;
	Point3dF light;
	Camera camera;
	float* zBuffer;
};

