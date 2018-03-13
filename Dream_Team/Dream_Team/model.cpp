#include "model.h"
#include <iostream>
#include <fstream>
#include <string>

Model::Model(const char* path) {

	std::ifstream input(path);
	std::string str;
	Point3dF point3d;
	Point2dF point2d;
	while (!input.eof())
	{
		input >> str;
		if (str == "v") {
			input >> point3d;
			vertices.push_back(point3d);
		}
		else if (str == "f") {
			int v1;
			char c;
			input >> v1;
			input >> c;
			if (c == ' ') {// format f v1 v2 v3
				int v2,v3;
				input >> v2 >> v3;
				Point3dI v(--v1, --v2, --v3);
				std::vector<Point3dI> f;
				f.push_back(v);
				faces.push_back(f);
			}
			else {
				input >> c;
				if (c == '/') {// format f v1//vn1 v2//vn2 v3//vn3
					int vn1, v2, vn2, v3, vn3;
					input >> vn1 >> v2 >> c >> c >> vn2 >> v3 >> c >> c >> vn3;
					Point3dI v(--v1, --v2, --v3);
					Point3dI vn(--vn1, --vn2, --vn3);
					std::vector<Point3dI> f;
					f.push_back(v);
					f.push_back(vn);
					faces.push_back(f);
				}
				else {// format f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3
					input.putback(c);
					int vn1, vt1, v2, vn2, vt2, v3, vn3, vt3;
					input >> vt1 >> c >> vn1 >> v2 >> c >> vt2 >> c >> vn2 >> v3 >> c >> vt3 >> c >> vn3;
					Point3dI v(--v1, --v2, --v3);
					Point3dI vt(--vt1, --vt2, --vt3);
					Point3dI vn(--vn1, --vn2, --vn3);
					std::vector<Point3dI> f;
					f.push_back(v);
					f.push_back(vt);
					f.push_back(vn);
					faces.push_back(f);
				}
			}		
		}else if (str == "vn"){
			input >> point3d;
			nvertices.push_back(point3d);
		}
		else if (str == "vt") {
			input >> point2d;
			tvertices.push_back(point2d);	
		}
		std::getline(input,str);
	}
	input.close();
}

int Model::vertsSize()
{
	return vertices.size();
}

int Model::facesSize()
{
	return faces.size();
}

int Model::nvertSize()
{
	return nvertices.size();
}

int Model::tvertSize()
{
	return tvertices.size();
}

std::vector<Point3dI> Model::face(int i)
{
	return faces.at(i);
}

std::vector<Point3dF> Model::verts(Point3dI i)
{
	std::vector<Point3dF> v;
	v.push_back(vertices.at(i.x));
	v.push_back(vertices.at(i.y));
	v.push_back(vertices.at(i.z));
	return v;
}

