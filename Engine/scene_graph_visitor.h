#ifndef ENGINE_SCENE_GRAPH_VISITOR_H
#define ENGINE_SCENE_GRAPH_VISITOR_H

class Component;
class Camera;
class SceneGraphVisitor
{
public:
	virtual void Apply(Camera) {}
};

#endif // !ENGINE_SCENE_GRAPH_VISITOR_H
