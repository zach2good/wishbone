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

}

SDL2Renderer::~SDL2Renderer()
{
  SDL_DestroyRenderer(m_pRenderer);
  SDL_DestroyWindow(m_pWindow);
}

void SDL2Renderer::clear(int _r, int _g, int _b)
{
  SDL_SetRenderDrawColor(m_pRenderer, _r, _g, _b, 255);
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
