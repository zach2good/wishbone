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
        tex = _tex;
        x = 0.0f;
        y = 0.0f;
        w = 1.0f;
        h = 1.0f;
    }

    // Use a subset of a texture, dictated by a spritesheet
	Sprite(SpriteSheet* ss, int i)
	{ 
		tex = ss->GetTexture();
        x = ss->GetSpriteX(i);
        y = ss->GetSpriteY(i);
        w = ss->GetSpriteW(i);
        h = ss->GetSpriteH(i);
	}

 private:
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

