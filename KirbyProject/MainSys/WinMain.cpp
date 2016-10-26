#include "MainSystem.h"
#include "Resource.h"

INT WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE, LPTSTR, INT)
{
	Mainsys sys;

	sys.Setup(hInst, IDI_TEST1);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(723921);

	return sys.Run();
}