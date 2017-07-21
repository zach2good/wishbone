#pragma once

#include <string>

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "glm/common.hpp"

#include "Texture.h"

class Sprite : public Component
{
public:

    Sprite(Texture* _tex) : Component(typeid(Sprite))
    {
        tex = _tex;
    }

    virtual ~Sprite() {}

    Texture* tex;

    glm::vec2 pivot = glm::vec2(0.5f, 0.5f);
    glm::vec2 uvdim = glm::vec2(1.0f, 1.0f);
    glm::vec2 uvoffset = glm::vec2(0.0f, 0.0f);
    glm::vec2 size = glm::vec2(0, 0);

    int frame = 0;

	bool flip = false;
};

