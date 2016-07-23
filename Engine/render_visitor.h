#ifndef ENGINE_RENDER_VISITOR_H
#define ENGINE_RENDER_VISITOR_H
#include "scene_graph_visitor.h"

class RenderVisitor : public SceneGraphVisitor
{
	virtual void Apply(Mesh&) override;
};

#endif // !ENGINE_RENDER_VISITOR_H
