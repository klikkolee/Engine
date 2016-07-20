#include "choreographer.h"
#include "game_object.h"
#include "SDL.h" //Must be included due to sdl's redefinition of main
#include <memory>
#include <assert.h>
int main(int argc, char* argv[])
{
	{
		auto gameObject1 = std::make_shared<GameObject>();
		auto gameObject2 = std::make_shared<GameObject>();
		auto gameObject3 = std::make_shared<GameObject>();
		/*gameObject2->addChild(*gameObject3);
		gameObject1->addChild(*gameObject2);
		gameObject1->addChild(*gameObject3);*/
		gameObject3->SetParent(gameObject2.get());
		gameObject2->SetParent(gameObject1.get());
		gameObject3->SetParent(gameObject1.get());
	}
	Choreographer::Start();

	return 0;
}