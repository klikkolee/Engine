#include "graph_node.h"
#include "scene_graph_visitor.h"

void GraphNode::Accept(SceneGraphVisitor& visitor)
{
	visitor.Apply(*this);
}

void GraphNode::Ascend(SceneGraphVisitor &)
{

}

void GraphNode::Descend(SceneGraphVisitor& visitor){}
