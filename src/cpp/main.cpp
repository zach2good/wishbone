#include <stdio.h>
#include <iostream>

// Defined in the build script
//#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h"

#include "rang.hpp"

int main(int argc, char* argv[]) 
{ 
	int width, height, bpp;
	unsigned char* rgb = stbi_load("myimage.png", &width, &height, &bpp, 3);
	stbi_image_free(rgb);

	rang::init();

	getchar();
	return 0;
}
