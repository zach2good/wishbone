#pragma once

#include "Texture.h"
#include "glm/vec4.hpp"

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
    // When it comes to rendering, these should be indisinguishable from eachother
    //
    SpriteSheet(Texture* tex, int x, int y)
        : texture(tex), x_split(x), y_split(y)
    {
		width = tex->width;
		height = tex->height;
    }
    
    ~SpriteSheet() { } 

	glm::vec4 getSrcRect(int x, int y)
	{
		return glm::vec4(x_split, y_split, x, y);
	}

    Texture* GetTexture()
    {
        return texture;
    }
    
 //private:
    Texture* texture;

    int x_split; 
    int y_split;  

	int width;
	int height;
};
