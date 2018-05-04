#include "ComplexGameSystemApp.h"
#include <crtdbg.h>

int main() {

	// allocation
	auto app = new ComplexGameSystemApp();

	// initialise and loop
	app->run("Audio Visualizer", 1900, 1000, false);

	// detects memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// deallocation
	delete app;

	return 0;
}