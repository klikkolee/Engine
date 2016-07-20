#include "scene.h"
#include "scene_graph_visitor.h"
#include "game_object.h"

void Scene::accept(SceneGraphVisitor & visitor)
{
	rootObject.Descend(visitor);
}
