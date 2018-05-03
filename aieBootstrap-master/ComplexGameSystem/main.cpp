#include "ComplexGameSystemApp.h"

int main() {
	
	// allocation
	auto app = new ComplexGameSystemApp();

	// initialise and loop
	app->run("Audio Visualizer", 1900, 1000, false);

	// deallocation
	delete app;

	return 0;
}