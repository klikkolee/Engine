#ifndef ENGINE_COMPONENT_H
#define ENGINE_COMPONENT_H
#include "graph_node.h"

class SceneGraphVisitor;
class Camera;
class GameObject;
class Component : public GraphNode
{
	friend class GameObject;
	GameObject* parentObject;
protected:
	Component(GameObject* parent);
	Component() = default;
	Component(const Component&) = default;
public:
	virtual Camera* AsCamera() { return nullptr; }
};

#endif // !ENGINE_COMPONENT_H
