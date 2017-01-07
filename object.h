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
		float x1;
		float x2;
		float x3;
		float y1;
		float y2;
		float y3;
		float z1;
		float z2;
		float z3;
		float xn1;
		float xn2;
		float xn3;
		float yn1;
		float yn2;
		float yn3;
		float zn1;
		float zn2;
		float zn3;
		polygon(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float xn1, float yn1, float zn1, float xn2, float yn2, float zn2, float xn3, float yn3, float zn3)
			: x1(x1), y1(y1), z1(z1), x2(x2), y2(y2), z2(z2), x3(x3), y3(y3), z3(z3), xn1(xn1), yn1(yn1), zn1(zn1), xn2(xn2), yn2(yn2), zn2(zn2), xn3(xn3), yn3(yn3), zn3(zn3)
		{}

	};
	struct point
	{
		float x;
		float y;
		float z;
		point(float x, float y, float z)
			: x(x), y(y), z(z)
		{}

	};
	
	Object(); 
	void Draw(int x_c2, int y_c2, float type);
	void DrawGuro(int x_c2, int y_c2, float type);
	void Rotate(float AngleX);
	void ReadObjectFromOBJ(const char* filename);
	string GetToken(string my_string);


private:
	float LightX, LightY, LightZ;
	int Dist;
	size_t marker;
	vector <polygon> faces;
};


