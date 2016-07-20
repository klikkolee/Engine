#ifndef ENGINE_GRAPH_NODE_H
#define ENGINE_GRAPH_NODE_H
#include <memory>
class SceneGraphVisitor;
class GameObject;
//Convienience class to reduce overloads of SceneGraphVisitor's Traversal functions
class GraphNode
{
protected:
	std::weak_ptr<GameObject> parent;
public:
	//applies Visitor to components
	virtual void Accept(SceneGraphVisitor&);
	//applies Visitor to components and components of parents
	virtual void Ascend(SceneGraphVisitor&);
	//applies Visitor to components and components of children
	virtual void Descend(SceneGraphVisitor&);
};

#endif // !ENGINE_GRAPH_NODE_H
