#pragma once

#include <string>

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "SpriteSheet.h"

class Sprite : public Component
{
public:

    // Use whole texture
    Sprite(Texture* _tex)
    {
        type = "sprite";

        tex = _tex;
        x = 0.0f;
        y = 0.0f;
        w = 1.0f;
        h = 1.0f;
    }

    // Use a subset of a texture, dictated by a spritesheet
    Sprite(SpriteSheet* ss, int x, int y)
    {
        type = "sprite";

        tex = ss->GetTexture();
        x = ss->GetSpriteX(x, y);
        y = ss->GetSpriteY(x, y);
        w = ss->GetSpriteW(x, y);
        h = ss->GetSpriteH(x, y);
    }

    Texture* tex;
    float x;
    float y;
    float w;
    float h;

    // TODO:
    // Rotation
    // Color
    // Scale
    // etc.
};

