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
		polygon(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
			: x1(x1), y1(y1), z1(z1), x2(x2), y2(y2), z2(z2), x3(x3), y3(y3), z3(z3)
		{}

	};
	struct my_vertex
	{
		float x;
		float y;
		float z;
		my_vertex(float x, float y, float z)
			: x(x), y(y), z(z)
		{}

	};
	
	Object(); 
	void Draw(SDL_Surface *screen, int x_c2, int y_c2, float type);
	void Rotate(float AngleX);
	void ReadObjectFromOBJ(const char* filename, SDL_Surface *screen);
	string GetToken(string my_string);


private:
	float LightX, LightY, LightZ;
	int Dist;
	int marker;
	vector <polygon> vv;
};


