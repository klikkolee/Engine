#ifndef ENGINE_COMPONENT_H
#define ENGINE_COMPONENT_H

class SceneGraphVisitor;
class Camera;
class GameObject;
class Component
{
	friend class GameObject;
	GameObject* parentObject;
protected:
	inline Component(GameObject* parent) { parentObject = parent; }
	Component() = default;
	Component(const Component&) = default;
public:
	virtual void Accept(SceneGraphVisitor&) {};
	virtual Camera* AsCamera() { return nullptr; }
};

#endif // !ENGINE_COMPONENT_H
