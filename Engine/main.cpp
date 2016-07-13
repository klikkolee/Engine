#include "choreographer.h"
#include "window.h"
#include "matrix4.h"
#include "SDL.h" //Must be included due to sdl's redefinition of main
#include <GL\glew.h>
#include "gsl.h"
#include <vector>
int main(int argc, char* argv[])
{
	Choreographer::Start();

	return 0;
}