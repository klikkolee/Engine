#ifndef ENGINE_SCENE_GRAPH_VISITOR_H
#define ENGINE_SCENE_GRAPH_VISITOR_H

class Component;
class Camera;
class GraphNode;
class Mesh;
class SceneGraphVisitor
{
protected:
	enum TraversalMode
	{
		MODE_ASCEND,
		MODE_DESCEND,
		MODE_NO_TRAVERSE
	}traversalMode = MODE_DESCEND;
	void Traverse(GraphNode&);
	inline SceneGraphVisitor(TraversalMode mode) : traversalMode(mode) {}
public:
	virtual void Apply(GraphNode&);
	virtual void Apply(Component&);
	virtual void Apply(Camera&);
	virtual void Apply(Mesh&);
};

#endif // !ENGINE_SCENE_GRAPH_VISITOR_H
