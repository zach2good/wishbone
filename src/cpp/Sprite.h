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
	Sprite(std::string _filename, std::string _name) : filename(_filename), name(_name) { type = "sprite"; }
	Sprite(std::string _filename, std::string _name, int x, int y, int w, int h) : filename(_filename), name(_name) 
	{ 
		type = "sprite"; 
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
	}

	std::string filename;
	std::string name;
	SDL_Rect rect;
};

