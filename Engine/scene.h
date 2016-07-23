#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H

#include "game_object.h"
#include <memory>
#include<vector>

class SceneGraphVisitor;
class Scene
{
	std::shared_ptr<GameObject> rootObject;
public:
	void TraverseWholeHierarchy(SceneGraphVisitor&);
	void AddObjectToTreeBase(GraphNode& object);
	inline Scene() : rootObject(std::make_shared<GameObject>()) {}
};

#endif // ENGINE_SCENE_H