#include "graph_node.h"
#include "scene_graph_visitor.h"
#include "transform.h"

void GraphNode::SetParent(Transform* parent)
{
	if (parent != nullptr)
	{
		parent->AddChild(*this);
		auto parentLock = this->parent.lock();
		if (parentLock.get() != nullptr)
			parentLock->RemoveChild(*this);
		this->parent = std::static_pointer_cast<Transform>(parent->shared_from_this());
	}
	else
		this->parent.reset();
}

std::weak_ptr<Transform> GraphNode::GetParent()
{
	return parent;
}

void GraphNode::Accept(SceneGraphVisitor& visitor)
{
	visitor.Apply(*this);
}

void GraphNode::Ascend(SceneGraphVisitor &)
{

}

void GraphNode::Descend(SceneGraphVisitor& visitor){}
