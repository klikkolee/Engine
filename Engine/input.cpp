#include "input.h"
#include "SDL.h"
#include <unordered_map>
template <class T>
static inline void hash_combine(std::size_t & seed, const T & v)
{
	std::hash<T> hasher;
	seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std
{
	template<typename S, typename T> struct hash<pair<S, T>>
	{
		inline size_t operator()(const pair<S, T> & v) const
		{
			size_t seed = 0;
			::hash_combine(seed, v.first);
			::hash_combine(seed, v.second);
			return seed;
		}
	};
}
namespace Input
{
	typedef std::pair<decltype(SDL_GetWindowID(nullptr)), decltype(SDL_KeyboardEvent::keysym.sym)> KeyStateKeyType;
	typedef std::pair<decltype(SDL_GetWindowID(nullptr)), decltype(SDL_MouseButtonEvent::button)> MouseButtonStateKeyType;
	static std::unordered_map<KeyStateKeyType, bool> keyState;
	static std::unordered_map<MouseButtonStateKeyType, bool> MouseButtonState;
	static std::unordered_map<decltype(SDL_GetWindowID(nullptr)), std::pair<decltype(SDL_MouseMotionEvent::xrel), decltype(SDL_MouseMotionEvent::yrel) >> MouseDelta; 
	
	void Input::ProcessEvent(SDL_Event event)
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			keyState.insert_or_assign(KeyStateKeyType(event.key.windowID,event.key.keysym.sym),true);
				break;
		case SDL_KEYUP:
			keyState.insert_or_assign(KeyStateKeyType(event.key.windowID, event.key.keysym.sym), false);
			break;
		case SDL_MOUSEBUTTONDOWN:
			break;
		case SDL_MOUSEBUTTONUP:
			break;
		case SDL_MOUSEMOTION:
			MouseDelta.insert_or_assign(event.motion.windowID, std::pair<decltype(event.motion.xrel),decltype(event.motion.yrel)>(event.motion.xrel, event.motion.yrel));
			break;
		default:
			break;
		}
	}
	bool IsKeyPressed(decltype(SDL_GetWindowID(nullptr)) windowID, decltype(SDL_Event::key.keysym.sym) key)
	{
		return keyState[KeyStateKeyType(windowID, key)];
	}
	Vector2 GetMouseDelta(decltype(SDL_GetWindowID(nullptr)) windowID)
	{
		return Vector2(MouseDelta[windowID].first,MouseDelta[windowID].second);
	}
}
