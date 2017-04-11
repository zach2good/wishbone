#include "renderer.h"

//#include "shared.h"

#include "SDL.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

int Renderer::init()
{
	//LOG_INFO(" Renderer::init()");
	if ((SDL_Init(SDL_INIT_VIDEO) == -1)) 
	{
		//LOG_ERROR("SDL_Init Error:");
		//LOG_ERROR(SDL_GetError());
		return -1;
	}

	return 0;
}

int Renderer::cleanup()
{
	return 0;
}
