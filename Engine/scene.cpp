#include "scene.h"
#include "scene_graph_visitor.h"
#include "game_object.h"

void Scene::TraverseWholeHierarchy(SceneGraphVisitor & visitor)
{
	rootObject->Accept(visitor);
}

void Scene::AddObjectToTreeBase(GraphNode & object)
{
	object.SetParent(rootObject.get());
}
