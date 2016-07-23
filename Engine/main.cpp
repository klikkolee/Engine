#include "choreographer.h"
#include "game_object.h"
#include "scene_graph_visitor.h"
#include "scene.h"
#include "log.h"
#include "SDL.h" //Must be included due to sdl's redefinition of main
#include <memory>
#include <assert.h>


class TestVisitor : public SceneGraphVisitor
{
public:
	inline virtual void Apply(GraphNode& node) override
	{
		Log("Visiting node at %p\n", &node);
		Traverse(node);
	}
	inline TestVisitor() : SceneGraphVisitor(MODE_DESCEND) {}
};

int main(int argc, char* argv[])
{
	{
		Scene scene;
		auto gameObject1 = std::make_shared<GameObject>();
		auto gameObject2 = std::make_shared<GameObject>();
		auto gameObject3 = std::make_shared<GameObject>();
		/*gameObject2->addChild(*gameObject3);
		gameObject1->addChild(*gameObject2);
		gameObject1->addChild(*gameObject3);*/
		gameObject3->SetParent(gameObject2.get());
		gameObject2->SetParent(gameObject1.get());
		gameObject3->SetParent(gameObject1.get());
		scene.AddObjectToTreeBase(*gameObject1);
		scene.TraverseWholeHierarchy(TestVisitor());
	}
	Choreographer::Start();

	return 0;
}