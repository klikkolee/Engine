#include "choreographer.h"
#include "window.h"
#include "SDL.h"
#include "GL\glew.h"
#include <vector>
#include <unordered_map>
namespace Choreographer
{
	bool isInitialized = false;
	bool isRunning = false;
	bool stopOnMainWindowClose = true;
	Window* mainWindow;
	std::unordered_map<int, Window*> windowMap;
	void MainLoop()
	{
		while (isRunning)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				if (event.type==SDL_WINDOWEVENT)
				{
					if (event.window.event==SDL_WINDOWEVENT_CLOSE)
					{
						delete windowMap.at(event.window.windowID);
						windowMap.erase(event.window.windowID);
						if (event.window.windowID==mainWindow->GetID()&&
							stopOnMainWindowClose)
						{
							Stop();
						}
					}
				}
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
	if (!isInitialized)
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

		windowMap.emplace(mainWindow->GetID(), mainWindow);
		isInitialized = true;
	}
	if (!isRunning)
	{
		isRunning = true;
		MainLoop();
	}
}

void Choreographer::Stop()
{
	isRunning = false;
	SDL_Quit();
}

void Choreographer::SetStopOnMainWindowClose(bool value)
{
	stopOnMainWindowClose = value;
}

void Choreographer::DeInitialize()
{
	isInitialized = false;
	Stop();
	//iterator to pairs where second is pointer to window
	std::unordered_map<int, Window*>::iterator windowMapIterator;
	for (windowMapIterator = windowMap.begin(); windowMapIterator!=windowMap.end(); ++windowMapIterator)
	{
		delete (*windowMapIterator).second;
	}
	windowMap.clear();
	mainWindow = NULL; //memory freed in for loop
}
