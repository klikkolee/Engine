#ifndef CHOREOGRAPHER_H
#define CHOREOGRAPHER_H
#include "window.hpp"

//namespace which controls the interaction of Engine components
//with each other and with the game code
namespace Choreographer
{
	//start main loop
	void Start();
	//stop main loop
	void Stop();
}
#endif // !CHOREOGRAPHER_H
