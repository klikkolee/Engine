#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <string>

class Window final
{
	int width;
	int height;
	std::string title;
	int sdlWindowID;
	SDL_Window* sdlWindow;
	SDL_GLContext sdlGLContext;
public:
	Window(int width, int height, const std::string& title);
	~Window();
	inline int GetID() { return sdlWindowID; }
	void SwapBuffers();
	void BindAsRenderTarget();
	inline void SetFullScreen(bool value) { SDL_SetWindowFullscreen(sdlWindow, value ? SDL_WINDOW_FULLSCREEN : 0); }
	inline void SetSize(int width, int height) { SDL_SetWindowSize(sdlWindow, width, height); }
};

#endif // !WINDOW_H
