#pragma once
#include <vector>
#include <string>
#include <cmath>
#include "mygraphicslib.h"
#include <SDL.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <SDL_timer.h>
using namespace std;

class Object {
public:
	struct polygon
	{
		float x1, x2, x3, y1, y2, y3, z1, z2, z3;
		float xn1, xn2, xn3, yn1, yn2, yn3, zn1, zn2, zn3;
	};
	struct point
	{
		float x, y, z;
	};
	
	Object(); 
	void Draw(int x_c2, int y_c2, float type);
	void DrawGuro(int x_c2, int y_c2, float type);
	void Rotate(float AngleX);
	void ReadObjectFromOBJ(const char* filename);
private:
	string GetToken(string my_string);
	float LightX, LightY, LightZ;
	int Dist;
	size_t marker;
	vector <polygon> faces;
};
