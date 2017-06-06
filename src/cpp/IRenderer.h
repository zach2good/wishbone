#pragma once

class SDL_Window;

class IRenderer 
{ 
public:
	virtual ~IRenderer() {};

	virtual void clear() = 0;
	virtual void draw() = 0;
	virtual void swap() = 0;
	
	virtual SDL_Window* getWindow() = 0;
};