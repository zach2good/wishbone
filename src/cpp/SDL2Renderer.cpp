#include "SDL2Renderer.h"

#include <iostream>
#include "stb_image.h"
#include "stb_easy_font.h"
#include "stb_truetype.h"

SDL2Renderer::SDL2Renderer(const char* _title, const int _width, const int _height)
{
	//Start SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL Error" << std::endl;
	}

	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(0, &current);

	// Start a Window
	m_pWindow = SDL_CreateWindow(_title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		_width, _height,
		SDL_WINDOW_SHOWN);

	if (!m_pWindow) {
		std::cout << "Window Error" << std::endl;
	}

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

	SDL_Surface* loadedSurface = nullptr;

	int w;
	int h;
	int comp;
	unsigned char* image = stbi_load("res/jetroid-sprites/player/idle/s01.png",
					 &w, &h, &comp,
					 STBI_rgb);
	if (image == nullptr)
	{
	  std::cout << "Could not load image" << std::endl;
	}
	else
	{
	  std::cout << "Loaded image" << std::endl;
	}
	stbi_image_free(image);

	SDL_FreeSurface(loadedSurface);

/*
	// Roboto-Black.ttf
	char buffer[24<<20];
	stbtt_fontinfo font;
	int i,j,ascent,baseline,ch=0;
	float scale, xpos=2; // leave a little padding in case the character extends left
	const unsigned char *text = "Heljo World!"; // intentionally misspelled to show 'lj' brokenness

	fread(buffer, 1, 1000000, fopen("c:/windows/fonts/arialbd.ttf", "rb"));
	stbtt_InitFont(&font, buffer, 0);

	scale = stbtt_ScaleForPixelHeight(&font, 15);
	stbtt_GetFontVMetrics(&font, &ascent,0,0);
	baseline = (int) (ascent*scale);
*/
}

SDL2Renderer::~SDL2Renderer()
{
  SDL_DestroyRenderer(m_pRenderer);
  SDL_DestroyWindow(m_pWindow);
}

void SDL2Renderer::clear(float _r, float _g, float _b)
{
  SDL_SetRenderDrawColor(m_pRenderer, (Uint8) 255.0f * _r, (Uint8) 255.0f * _g, (Uint8) 255.0f * _b, 255);
  SDL_RenderClear(m_pRenderer);
}

void SDL2Renderer::draw()
{
  // Draw anything that was submitted, probably a pointer to the world state
}

void SDL2Renderer::swap()
{
  SDL_RenderPresent(m_pRenderer);
}
