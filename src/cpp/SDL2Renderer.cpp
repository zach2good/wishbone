#include "SDL2Renderer.h"

#include <iostream>

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

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cout << " Failed to initialize IMG : " << SDL_GetError() << std::endl;
	}

	if (TTF_Init() < 0)
	{
		std::cout << " Failed to initialize TTF : " << SDL_GetError() << std::endl;
	}

	font = TTF_OpenFont("res/Roboto-Black.ttf", 20);

	if (font == nullptr)
	{
		std::cout << " Failed to load font : " << SDL_GetError() << std::endl;
	}
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
	SDL_Surface* solid = TTF_RenderText_Solid(font, "Wishbone", textColor);
	textTexture = SDL_CreateTextureFromSurface(m_pRenderer, solid);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
	textRect.x = 0;
	textRect.y = 0;
	SDL_RenderCopy(m_pRenderer, textTexture, nullptr, &textRect);
}

void SDL2Renderer::swap()
{
  SDL_RenderPresent(m_pRenderer);
}
