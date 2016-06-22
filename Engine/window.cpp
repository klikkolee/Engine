#include "window.hpp"
#include "SDL.h"

Window::~Window()
{
	SDL_GL_DeleteContext(sdlGLContext);
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();
}

void Window::SwapBuffers()
{
	SDL_GL_SwapWindow(sdlWindow);
}

Window::Window(int width, int height, const std::string & title)
{
	sdlWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
								 SDL_WINDOWPOS_CENTERED, width, height,
								 SDL_WINDOW_OPENGL);
	sdlGLContext = SDL_GL_CreateContext(sdlWindow);
}
