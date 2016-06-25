#include "scene_manager.hpp"
#include <unordered_map>
#include <vector>
#include "game_object.hpp"

namespace
{
	std::unordered_map<int, GameObject*> objects;
	std::vector<int> rootObjects;
}

GameObject * SceneManager::GetGameObject(int id)
{
	return objects.at(id);
}
