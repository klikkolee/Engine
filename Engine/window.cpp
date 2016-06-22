#include "window.hpp"
#include "SDL.h"
#include "GL\glew.h"

Window::~Window()
{
	SDL_GL_DeleteContext(sdlGLContext);
	SDL_DestroyWindow(sdlWindow);
}

void Window::SwapBuffers()
{
	SDL_GL_SwapWindow(sdlWindow);
}

void Window::BindAsRenderTarget()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 1, 1);
}

Window::Window(int width, int height, const std::string & title)
{
	sdlWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
								 SDL_WINDOWPOS_CENTERED, width, height,
								 SDL_WINDOW_OPENGL);
	sdlWindowID = SDL_GetWindowID(sdlWindow);
	sdlGLContext = SDL_GL_CreateContext(sdlWindow);
}
