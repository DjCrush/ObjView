#include "mygraphicslib.h"
const int WIDTH = 1024;
const int HEIGHT = 768;
const int WH = HEIGHT*WIDTH;
const int BPP = 4;
const int DEPTH = 32;
const float M_PI = 3.1415926535897932384626433832795028841971f / 180;
int *Z_buffer = new int[WIDTH * HEIGHT * 10];

void ClsScreen()
{
	for (int x = 0; x < HEIGHT*WIDTH; x++)	*memory_screen++ = 2949247;
}

void inline SetPixel(int x, int y, int col)
{
	Uint32 *pixmem32;
	int ytimesw = y*(screen->pitch >> 2);
	pixmem32 = (Uint32*)screen->pixels + ytimesw + x;
	*pixmem32 = (col<<16) | (col<<8) | (col);
}


void Triangle(int x1, int x2, int x3, int y1, int y2, int y3, int z1, int z2, int z3, int col)
{
	if ((x1 < 0 & x2 < 0 & x3 < 0) || (x1 > WIDTH & x2 > WIDTH & x3 > WIDTH) || (y1 < 0 & y2 < 0 & y3 < 0) || (y1 > HEIGHT & y2 > HEIGHT & y3 > HEIGHT)) return;
	int x11, x12, z11, z12;
	int idx, zbb, y, x;
	float alpha, beta, th, sh;
	if (y1 > y2) { swap(y1, y2); swap(x1, x2); swap(z1, z2); }
	if (y1 > y3) { swap(y1, y3); swap(x1, x3); swap(z1, z3); }
	if (y2 > y3) { swap(y2, y3); swap(x2, x3); swap(z2, z3); }
	th = y3 - y1;
	sh = y2 - y1;
	if(th!=0 && sh!=0)
	{
		for (y = y1; y < y2; y++)
		{
			alpha = (float)(y - y1) / th;
			beta = (float)(y - y1) / sh;
			x11 = x1 + (x3 - x1)*alpha;
			x12 = x1 + (x2 - x1)*beta;
			z11 = z1 + (z3 - z1)*alpha;
			z12 = z1 + (z2 - z1)*beta;
			if (x12 < x11) { swap(x11, x12); swap(z11, z12); }
			alpha = (z12 - z11) / (x12 - x11 + 0.000000000001);
			for(x = x11; x < x12; x++)
			{
				if ((x > 0 && x < WIDTH) && (y > 0 && y < HEIGHT))
				{
					zbb = (x - x11) * alpha + z11;
					idx = x + (y << 10);
					if (Z_buffer[idx] < zbb)
					{
						Z_buffer[idx] = zbb;
						SetPixel(x, y, col);
					}
				}
			}
		}
	}
	sh = y3 - y2;
	if (th != 0 && sh != 0)
	{
		for(y = y2; y < y3; y++)
		{
			alpha = (float)(y - y1) / th;
			beta = (float)(y - y2) / sh;
			x11 = x1 + (x3 - x1)*alpha;
			x12 = x2 + (x3 - x2)*beta;
			z11 = z1 + (z3 - z1)*alpha;
			z12 = z2 + (z3 - z2)*beta;
			if (x12 < x11) 
			{ 
				swap(x11, x12); 
				swap(z11, z12); 
			}
			alpha = (z12 - z11) / (x12 - x11 + 0.000000000001);
			for (x = x11; x < x12; x++)
			{
				if ((x > 0 && x < WIDTH) && (y > 0 && y < HEIGHT))
				{
					zbb = (x - x11) * alpha + z11;
					idx = x + (y << 10);
					if (Z_buffer[idx] < zbb)
					{
						Z_buffer[idx] = zbb;
						SetPixel(x, y, col);
					}
				}
			}
		}
	}
}

void TriangleGradient(int x1, int x2, int x3, int y1, int y2, int y3, int z1, int z2, int z3, int col1, int col2, int col3)
{
	if ((x1 < 0 & x2 < 0 & x3 < 0) || (x1 > WIDTH & x2 > WIDTH & x3 > WIDTH) || (y1 < 0 & y2 < 0 & y3 < 0) || (y1 > HEIGHT & y2 > HEIGHT & y3 > HEIGHT)) return;
		int x11, x12, z11, z12, xo1 = x1, xo2 = x2, xo3 = x3, yo1 = y1, yo2 = y2, yo3 = y3;
		int Denom = x3 * (y1 - y2) + x1 * (y2 - y3) + x2 *  (y3 - y1);
		int sann = x3*y1 - y3*x1, tann = x1*y2 - y1*x2, snn, tnn;
		int idx, zbb, y, x, col;
		float alpha, beta, th, sh;
		if (!Denom) Denom = 1;
		if (y1 > y2) { swap(y1, y2); swap(x1, x2); swap(z1, z2); }
		if (y1 > y3) { swap(y1, y3); swap(x1, x3); swap(z1, z3); }
		if (y2 > y3) { swap(y2, y3); swap(x2, x3); swap(z2, z3); }
		th = y3 - y1;
		sh = y2 - y1;
		if (th != 0 && sh != 0)
		{
			for (y = y1; y < y2; y++)
			{
				alpha = (float)(y - y1) / th;
				beta = (float)(y - y1) / sh;
				x11 = x1 + (x3 - x1)*alpha;
				x12 = x1 + (x2 - x1)*beta;
				z11 = z1 + (z3 - z1)*alpha;
				z12 = z1 + (z2 - z1)*beta;
				if (x12 < x11) { swap(x11, x12); swap(z11, z12); }
				alpha = (z12 - z11) / (x12 - x11 + 0.0000001);
				for (x = x11; x < x12; x++)
				{
					if ((x > 0 && x < WIDTH) && (y > 0 && y < HEIGHT))
					{
						zbb = (x - x11) * alpha + z11;
						idx = x + (y << 10);
						if (Z_buffer[idx] < zbb)
						{
							Z_buffer[idx] = zbb;
							snn = ((sann + y * (xo1 - xo3) + x * (yo3 - yo1)) << 8) / Denom;
							tnn = ((tann + y * (xo2 - xo1) + x * (yo1 - yo2)) << 8) / Denom;
							col = (col1 * (255 - snn - tnn) + col2 * snn + col3 * tnn) >> 8;
							SetPixel(x, y, col);
						}
					}
				}
			}
		}
		sh = y3 - y2;
		if (th != 0 && sh != 0)
		{
			for (y = y2; y < y3; y++)
			{
				alpha = (float)(y - y1) / th;
				beta = (float)(y - y2) / sh;
				x11 = x1 + (x3 - x1)*alpha;
				x12 = x2 + (x3 - x2)*beta;
				z11 = z1 + (z3 - z1)*alpha;
				z12 = z2 + (z3 - z2)*beta;
				if (x12 < x11) { swap(x11, x12); swap(z11, z12); }
				alpha = (z12 - z11) / (x12 - x11 + 0.0000001);
				for (x = x11; x < x12; x++)
				{
					if ((x > 0 && x < WIDTH) && (y > 0 && y < HEIGHT))
					{
						zbb = (x - x11) * alpha + z11;
						idx = x + (y << 10);
						if (Z_buffer[idx] < zbb)
						{
							Z_buffer[idx] = zbb;
							snn = ((sann + y * (xo1 - xo3) + x * (yo3 - yo1)) << 8) / Denom;
							tnn = ((tann + y * (xo2 - xo1) + x * (yo1 - yo2)) << 8) / Denom;
							col = (col1 * (255 - snn - tnn) + col2 * snn + col3 * tnn) >> 8;
							SetPixel(x, y, col);
						}
					}
				}
			}
		}

}
