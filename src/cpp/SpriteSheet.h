#pragma once

#include "Texture.h"

class SpriteSheet
{
 public:
    // Note: This is just to act as a wrapper around a texture to get the X and Y
    // information for that sprite in the spritesheet.
    // 
    // Texture -> SpriteSheet -> Sprite (Component)
    //
    // Therefore, a non-SpriteSheet Sprite can be a wrapper around a texture on its own
    //
    // Texture -> Sprite (Component)
    //
    // When it comes to rendering, these should be indhisinguishable from eachother
    //
    SpriteSheet(Texture* tex, int x, int y)
        : texture(tex), x_split(x), y_split(y)
    {
        // ===
    }
    
    ~SpriteSheet() { } 

    float GetSpriteX(int index)
    {
        // TODO: Debug me
        float x_mult = (float)((texture->width / x_split) / texture->width);
        int row_index = index / x_split;
        return x_mult * (float)row_index;
    }

    float GetSpriteY(int index)
    {
        return 0.0f;
    }

    float GetSpriteW(int index)
    {
        return texture->width / x_split;;
    }

    float GetSpriteH(int index)
    {
        return texture->height / y_split;
    }

    Texture* GetTexture()
    {
        return texture;
    }
    
 private:
    Texture* texture;
    int x_split; // 4
    int y_split; // 2    
};
