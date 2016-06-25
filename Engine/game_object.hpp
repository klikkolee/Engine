#ifndef ENGINE_GAME_OBJECT_H
#define ENGINE_GAME_OBJECT_H
#include "transform.hpp"
#include "component.hpp"
#include <unordered_map>
class GameObject
{
	static int lastID;
	static int NextId() { return ++lastID; }
	int id;
	Transform transform;
	std::unordered_multimap<std::string, Component> components;
public:
	Transform GetTransform();
	void SetTransform(Transform transform);
	int GetID() { return id; }
};

#endif // !ENGINE_GAME_OBJECT_H
