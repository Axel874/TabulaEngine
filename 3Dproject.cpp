#include "pch.h"
#include "Core.h"
void StartHeapControl();
void DumpMemoryLeaks();

int main(int argc, char* argv[])
{
	StartHeapControl();
	{//scope for mem check
		const Window w{
			"My little program",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			512,512, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE,true,60
		};

		Core core = Core(w, true);
		core.Run();
	}
	DumpMemoryLeaks();
	return 0;
}

void StartHeapControl()
{
#if defined(DEBUG) | defined(_DEBUG)
	// Notify user if heap is corrupt
	
	//HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	// Report detected leaks when the program exits
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Set a breakpoint on the specified object allocation order number
	//_CrtSetBreakAlloc(538);
#endif
}
void DumpMemoryLeaks()
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif
}