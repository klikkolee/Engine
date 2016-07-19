#include "choreographer.h"
#include "transform.h"
#include "SDL.h" //Must be included due to sdl's redefinition of main
#include <memory>
int main(int argc, char* argv[])
{
	auto transform1 = std::make_shared<Transform>();
	auto transform2 = std::make_shared<Transform>();
	auto transform3 = std::make_shared<Transform>();
	transform3->SetParent(transform2.get());
	transform2->SetParent(transform1.get());
	transform3->SetParent(transform1.get());
	Choreographer::Start();

	return 0;
}