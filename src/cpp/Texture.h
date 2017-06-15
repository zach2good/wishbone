#pragma once

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "common.h"

class Texture
{
public:
	Texture()
	{
		// Take useful bits from here:
		// https://learnopengl.com/#!Getting-started/Textures
	}
	~Texture();

private:

};
