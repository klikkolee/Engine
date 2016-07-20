#ifndef ENGINE_GRAPH_NODE_H
#define ENGINE_GRAPH_NODE_H
#include <memory>
class SceneGraphVisitor;
class Transform;
//Convienience class to reduce overloads of SceneGraphVisitor's Traversal functions
class GraphNode : public std::enable_shared_from_this<GraphNode>
{
protected:
	std::weak_ptr<Transform> parent;
public:
	void SetParent(Transform*);
	Transform* GetParent();
	//applies Visitor to components
	virtual void Accept(SceneGraphVisitor&);
	//applies Visitor to components and components of parents
	virtual void Ascend(SceneGraphVisitor&);
	//applies Visitor to components and components of children
	virtual void Descend(SceneGraphVisitor&);
};

#endif // !ENGINE_GRAPH_NODE_H
