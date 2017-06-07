#pragma once

// SDL
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <glad/glad.h>


class IRenderer 
{ 
public:
	virtual ~IRenderer() {};

	virtual void clear(int _r, int _g, int _b) = 0;
	virtual void submit() = 0;
	virtual void draw() = 0;
	virtual void swap() = 0;
	
	virtual SDL_Window* getWindow() = 0;
};
