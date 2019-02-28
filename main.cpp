#include <SDL.h>
#include <cstdlib>
#include <Windows.h>
#include "mygraphicslib.h"
#include "object.h"
using namespace std;

SDL_Surface *screen;
SDL_Surface *font;

int wmain(int argc, wchar_t *argv[], wchar_t *envp[])
{
	SDL_Event event;
	int keypress = 0;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;
	if (!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE)))
	{
		SDL_Quit();
		return 1;
	}

	if (!(font = SDL_LoadBMP("font.bmp")))
	{
		
		MessageBoxA(NULL, "File 'font.bmp' not found", "Error", MB_OK);

		SDL_Quit();
		return 1;
	}
	Object tor;
	//tor.ReadObjectFromOBJ("E:/EXP/3dmax/obj/alfa147.obj"); float scale = 3;
	tor.ReadObjectFromOBJ("E:/EXP/3dmax/obj/1.obj"); float scale = 300;
	//tor.ReadObjectFromOBJ("mod.obj"); float scale = 3;
	//tor.ReadObjectFromOBJ("E:/EXP/3dmax/obj/bmw.obj"); float scale = 0.5;
	//tor.ReadObjectFromOBJ("E:/EXP/3dmax/obj/hand/hand.obj"); float scale = 200;
	while (!keypress)
	{
		ClearScreen();
	//	tor.Draw(WIDTH / 2, HEIGHT / 2, scale);
		tor.DrawGuro(WIDTH / 2, HEIGHT / 2, scale);
		tor.Rotate(0.5);
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
	}
	SDL_FreeSurface(font);
	SDL_FreeSurface(screen);
	SDL_Quit();
	delete[] Z_buffer;
	return 0;
}
