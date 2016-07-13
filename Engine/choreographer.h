#ifndef ENGINE_CHOREOGRAPHER_H
#define ENGINE_CHOREOGRAPHER_H

//namespace which controls the interaction of Engine components
//with each other and with the game code
namespace Choreographer
{
	//start main loop
	void Start();
	//stop main loop
	void Stop();
	void SetStopOnMainWindowClose(bool value);
}
#endif // !ENGINE_CHOREOGRAPHER_H
