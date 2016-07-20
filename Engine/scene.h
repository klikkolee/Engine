#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H

#include "game_object.h"
#include<vector>

class SceneGraphVisitor;
class Scene
{
	std::vector<GameObject> objects;
	GameObject rootObject;
public:
	void accept(SceneGraphVisitor&);
};

#endif // ENGINE_SCENE_H