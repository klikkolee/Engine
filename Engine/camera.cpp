#include "camera.h"
#include "scene_graph_visitor.h"

void Camera::Accept(SceneGraphVisitor & visitor)
{
	visitor.Apply(*this);
}
