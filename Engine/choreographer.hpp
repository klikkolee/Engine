#ifndef CHOREOGRAPHER_H
#define CHOREOGRAPHER_H

//namespace which controls the interaction of Engine components
//with each other and with the game code
namespace Choreographer
{
	//start main loop
	void Start();
	//stop main loop
	void Stop();
	void SetStopOnMainWindowClose(bool value);
	//stops main loop and undoes all internal setup.
	//redone on next start call
	void DeInitialize();
}
#endif // !CHOREOGRAPHER_H
