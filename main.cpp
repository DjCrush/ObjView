#include <SDL.h>
#include <Windows.h>
#include "graphicslib.h"
#include "mesh.h"
using namespace std;

SDL_Surface *screen;
SDL_Surface *font;
SDL_Renderer *renderer;
int *Z_buffer = new int[WIDTH * HEIGHT];

int wmain(int argc, wchar_t *argv[], wchar_t *envp[])
{
	SDL_Event event;
	SDL_Window *window = NULL;
	int keypress = 0;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;

	window = SDL_CreateWindow(
		"ObjViewer",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		WIDTH,                               // width, in pixels
		HEIGHT,                               // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
	);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (!(font = SDL_LoadBMP("font.bmp")))
	{
		MessageBoxA(NULL, "File 'font.bmp' not found", "Error", MB_OK);
		SDL_Quit();
		return 1;
	}
	Mesh tor;
	tor.Read("E:/EXP/3dmax/obj/alfa147.obj");
	while (!keypress)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				keypress = 1;
				break;
			case SDL_KEYDOWN:
				keypress = 1;
				break;
			}
		}
		SDL_RenderClear(renderer);
		ClearScreen();
		//tor.Draw(WIDTH / 2, HEIGHT / 2);
		tor.DrawGuro(WIDTH / 2, HEIGHT / 2);
		tor.Rotate(0.1);
		SDL_RenderPresent(renderer);
	}
	delete[] Z_buffer;
	SDL_FreeSurface(font);
	SDL_FreeSurface(screen);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
