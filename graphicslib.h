#pragma once
#include <vector>
#include <SDL.h>
#include <limits>
using namespace std;

const int WIDTH = 1600;
const int HEIGHT = 800;
const int BPP = 4;
const int DEPTH = 32;
const double DEG = 0.01745329251994329576923690768489;
extern SDL_Renderer *renderer;
extern SDL_Surface* screen;
extern SDL_Surface* font;

extern int* Z_buffer;

inline void SetPixel(int x, int y, int col);
void ClearScreen();
void Triangle(int x1, int x2, int x3, int y1, int y2, int y3, int z1, int z2, int z3, int col);
void TriangleGradient(double x1, double x2, double x3, double y1, double y2, double y3, double z1, double z2, double z3, int col1, int col2, int col3);
