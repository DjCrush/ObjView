#include <SDL.h>
#include <cstdlib>
#include "mygraphicslib.h"
#include "object.h"

using namespace std;


int wmain(int argc, wchar_t *argv[], wchar_t *envp[])
{
	SDL_Event event;
	SDL_Surface *screen;
	int keypress = 0;
	





	if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;

	
	if (!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE)))
	{
		SDL_Quit();
		return 1;
	}
	
	font = SDL_LoadBMP("font.bmp");

	Object tor;
//	tor.ReadObjectFromOBJ("E:/EXP/3dmax/obj/alfa147.obj", screen); float scale = 3;
	tor.ReadObjectFromOBJ("E:/EXP/3dmax/obj/1.obj", screen); float scale = 300;
	//tor.ReadObjectFromOBJ("mod.obj"); float scale = 3;
	//tor.ReadObjectFromOBJ("E:/EXP/3dmax/obj/bmw/BMWX12013/BMW X1 Obj (w).obj", screen); float scale = 0.5;
	//tor.ReadObjectFromOBJ("E:/EXP/3dmax/obj/hand/hand.obj", screen); float scale = 200;

	while (!keypress)
	{
		ClsScreen(screen);
		tor.Draw(screen, WIDTH / 2, HEIGHT / 2, scale);
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

	


	
	SDL_FreeSurface(screen);
	SDL_Quit();


	delete Z_buffer;

	return 0;
}

