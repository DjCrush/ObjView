#pragma once
#include <vector>
#include <string>
#include <cmath>
#include "graphicslib.h"
#include <SDL.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <SDL_timer.h>
using namespace std;

class Mesh{
public:
	struct Point
	{
		Point(double x, double y, double z, double xn, double yn, double zn) : x(x), y(y), z(z), xn(xn), yn(yn), zn(zn) {}
		double x, y, z, xn, yn, zn;
	};
	struct Polygon
	{
		Polygon(Point p1, Point p2, Point p3) : p1{ p1 }, p2{ p2 }, p3{ p3 } {}
		Point p1, p2, p3;
	};
	Mesh();
	void Draw(int x_c2, int y_c2);
	void DrawGuro(int x_c2, int y_c2);
	void Rotate(double AngleX);
	void Read(const char* filename);
private:
	string GetToken(string my_string);
	double LightX, LightY, LightZ;
	double Dist;
	size_t marker;
	vector <Polygon> faces;
};
