#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H

#include "vector2.h"
#include "render_target.h"
#include <SDL.h>
#include <string>

class Window final : public IRenderTarget
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
	inline Vector2 GetCenter() { return Vector2(width/2, height/2); }
	inline double GetHeight() { return height; }
	inline double GetWidth() { return width; }
	inline int GetID() { return sdlWindowID; }
	void SwapBuffers();
	virtual void BindAsRenderTarget();
	inline void SetFullScreen(bool value) { SDL_SetWindowFullscreen(sdlWindow, value ? SDL_WINDOW_FULLSCREEN : 0); }
	inline void SetSize(int width, int height) { SDL_SetWindowSize(sdlWindow, width, height); }
};

#endif // !ENGINE_WINDOW_H
