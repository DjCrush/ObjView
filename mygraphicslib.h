#pragma once
#include <vector>
#include <SDL.h>

using namespace std;

extern const int WIDTH;
extern const int HEIGHT;
extern const int BPP;
extern const int DEPTH;
extern const float M_PI;
extern SDL_Surface *screen;
extern SDL_Surface *font;

extern int *Z_buffer;

void inline SetPixel(int x, int y, int col);
void ClsScreen();
void Triangle(int x1, int x2, int x3, int y1, int y2, int y3, int z1, int z2, int z3, int col);
void TriangleGradient(int x1, int x2, int x3, int y1, int y2, int y3, int z1, int z2, int z3, int col1, int col2, int col3);
