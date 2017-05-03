#include <stdio.h>
#include <iostream>

#include "shared.h"
#include "renderer.h"

#include "ServiceLocator.h"

int main(int argc, char* argv[]) 
{ 
	LOG("Wishbone");

	// Stub in null systems
	//ServiceLocator::initialize();

	// Set up systems in order
	//ServiceLocator::provide(new NullAudioSystem());

	// Access systems
	//auto audio = ServiceLocator::getAudio();
	
	LOG_ERROR("LOG_ERROR");
	LOG_WARN("LOG_WARN");
	LOG_INFO("LOG_INFO");	

	Renderer ren;
	ren.init();

	ren.cleanup();

	error("ERR", "1", 1);
	
	LOG("Goodbye");
	getchar();
	return 0;
}
