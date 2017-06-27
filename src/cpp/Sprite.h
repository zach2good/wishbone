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
		// TODO: Fix me
        type = "sprite";

        tex = _tex;
        x = 0.0f;
        y = 0.0f;
        w = 1.0f;
        h = 1.0f;
    }

    // Use a subset of a texture, dictated by a spritesheet
    Sprite(SpriteSheet* _ss, int _x, int _y)
    {
        type = "sprite";

		tex = _ss->GetTexture();
		auto ss = _ss->getSrcRect(_x, _y);
		x = ss.x;
		y = ss.y;
		w = ss.z;
		h = ss.w;
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

