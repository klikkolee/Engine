#include "graph_node.h"
#include "scene_graph_visitor.h"
#include "transform.h"

void GraphNode::SetParent(Transform* parent)
{
	if (parent != nullptr)
	{
		parent->AddChild(*this);
		this->parent = std::static_pointer_cast<Transform>(parent->shared_from_this());
	}
	else
		this->parent.reset();
}

Transform * GraphNode::GetParent()
{
	return parent.lock().get();
}

void GraphNode::Accept(SceneGraphVisitor& visitor)
{
	visitor.Apply(*this);
}

void GraphNode::Ascend(SceneGraphVisitor &)
{

}

void GraphNode::Descend(SceneGraphVisitor& visitor){}
