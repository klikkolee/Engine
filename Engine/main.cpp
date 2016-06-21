#include "matrix4.hpp"
#include "transform.hpp"
#include "window.h"
#include "SDL.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

//TODO: move responsibility for SDL events to relevent classes once
//they are created
int main(int argc, char* argv[])
{
	Window gameWindow = Window(800,600,"test game");
	bool running = true;
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type==SDL_QUIT)
				running = false;
		}
	}

	return 0;
}