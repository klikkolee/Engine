#include "choreographer.h"
#include "SDL.h" //Must be included due to sdl's redefinition of main

int main(int argc, char* argv[])
{
	Choreographer::Start();
	return 0;
}