#include "choreographer.hpp"
#include "window.hpp"
#include "SDL.h"
#include "GL\glew.h"

namespace Choreographer
{
	bool isRunning = false;
	Window* mainWindow;
	void MainLoop()
	{
		while (isRunning)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				if (event.type==SDL_QUIT)
				{
					Stop();
				}
				//TODO: dispatch events to relevant structures once they exist
			}
		}

	}
}

void Choreographer::Start()
{
	if (!isRunning)
	{
		SDL_Init(SDL_INIT_EVERYTHING);

		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

		SDL_GL_SetSwapInterval(1);

		GLenum glewError = glewInit();
		if (glewError!=GLEW_OK)
		{
			fprintf(stderr, "Error: '%s'\n", glewGetErrorString(glewError));
		}

		mainWindow = new Window(800, 600, "Title");
		isRunning = true;
		MainLoop();
	}
	isRunning = true;
}

void Choreographer::Stop()
{
	isRunning = false;
}
