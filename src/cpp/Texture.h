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

#include <glad/glad.h>

//#include "common.h"

class Texture
{
public:
    Texture(std::string filename);
    ~Texture();

    GLuint ID;
    int width, height, nrChannels;
    const char* filename;

    void Bind() const;

private:

};
