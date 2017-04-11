#include <stdio.h>
#include <iostream>

#include "shared.h"
#include "renderer.h"

int main(int argc, char* argv[]) 
{ 
	LOG("Wishbone");
	
	LOG_ERROR("LOG_ERROR");
	LOG_WARN("LOG_WARN");
	LOG_INFO("LOG_INFO");	

	Renderer ren;
	ren.init();

	ren.cleanup();
	
	LOG("Goodbye");
	getchar();
	return 0;
}
