#ifndef ENGINE_SCENE_GRAPH_VISITOR_H
#define ENGINE_SCENE_GRAPH_VISITOR_H

class Component;
class Camera;
class GraphNode;
class SceneGraphVisitor
{
protected:
	enum
	{
		MODE_ASCEND,
		MODE_DESCEND,
		MODE_NO_TRAVERSE
	}traversalMode = MODE_DESCEND;
	void Traverse(GraphNode&);
public:
	inline virtual void Apply(GraphNode&) {}
	inline virtual void Apply(Component&) {}
	inline virtual void Apply(Camera&) {}
};

#endif // !ENGINE_SCENE_GRAPH_VISITOR_H
