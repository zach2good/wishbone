#pragma once

#include <string>

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

class Sprite : public Component
{
public: 
	Sprite(std::string _name, int x, int y, int w, int h) : name(_name) 
	{ 
		type = "sprite"; 
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
	}

	std::string name;
	SDL_Rect rect;
};

