#ifndef ENGINE_GAME_OBJECT_H
#define ENGINE_GAME_OBJECT_H

#include "transform.h"
#include "component.h"
#include "graph_node.h"
#include <vector>
#include <memory>

class SceneGraphVisitor;
class GameObject final : public GraphNode
{
	std::vector<std::unique_ptr<Component>> components;
public:
	Transform transform;
	

	template<class _Component, class = std::enable_if_t<std::is_base_of<Component,_Component>::value>>
	void AddComponent();
};

template<class _Component, class>
inline void GameObject::AddComponent()
{
	components.emplace_back(std::make_unique<_Component>(this));
}

#endif // !ENGINE_GAME_OBJECT_H
