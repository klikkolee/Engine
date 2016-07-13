#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H
#include "SDL.h"
#include "vector2.h"
namespace Input
{
	void ProcessEvent(SDL_Event event);
	bool IsKeyPressed(decltype(SDL_GetWindowID(nullptr)) windowID, decltype(SDL_Event::key.keysym.sym) key);
	Vector2 GetMouseDelta(decltype(SDL_GetWindowID(nullptr)) windowID);
}
#endif // !ENGINE_INPUT_H
