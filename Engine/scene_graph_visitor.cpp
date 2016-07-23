#include "scene_graph_visitor.h"
#include "camera.h"
#include "component.h"
#include "mesh.h"

void SceneGraphVisitor::Traverse(GraphNode & node)
{
	if (traversalMode == MODE_DESCEND)
	{
		node.Descend(*this);
	}
	else if(traversalMode == MODE_ASCEND)
	{
		node.Ascend(*this);
	}
}

void SceneGraphVisitor::Apply(GraphNode & node)
{
	Traverse(node);
}

void SceneGraphVisitor::Apply(Component & node)
{
	Apply(static_cast<GraphNode&>(node));
}

void SceneGraphVisitor::Apply(Camera & node)
{
	Apply(static_cast<Component&>(node));
}

void SceneGraphVisitor::Apply(Mesh & node)
{
	Apply(static_cast<Component&>(node));
}