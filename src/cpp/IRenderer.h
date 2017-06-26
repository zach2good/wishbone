#pragma once

// SDL
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <glad/glad.h>

#include <vector>
class World;

class IRenderer
{
public:
    virtual ~IRenderer() {};

    virtual void clear() = 0;
    virtual void submit(World* _world) = 0;
    virtual void draw() = 0;
    virtual void swap() = 0;

    virtual SDL_Window* getWindow() = 0;
};
