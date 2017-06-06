#pragma once


// SDL
#ifdef _WIN32
#include <SDL.h>
#include <glad/glad.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#endif


class IRenderer 
{ 
public:
	virtual ~IRenderer() {};

	virtual void clear() = 0;
	virtual void draw() = 0;
	virtual void swap() = 0;
	
	virtual SDL_Window* getWindow() = 0;
};