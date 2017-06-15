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

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr)
	{
		// Take useful bits from here:
		// https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader.h
	}
	~Shader();

private:

};
