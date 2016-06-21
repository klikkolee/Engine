#include "window.h"
//#include "SDL.h"
//#define GLEW_STATIC
#include "GL\glew.h"

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
	//TODO: move responsibility for initializing SDL and glew
	//out of window class to facilitate multiple windows
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

	sdlWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
								 SDL_WINDOWPOS_CENTERED, width, height,
								 SDL_WINDOW_OPENGL);
	sdlGLContext = SDL_GL_CreateContext(sdlWindow);

	SDL_GL_SetSwapInterval(1);

	GLenum glewError = glewInit();
	if (glewError!=GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(glewError));
	}


}
