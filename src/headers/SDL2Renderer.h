#pragma once

#include "IRenderer.h"
#include "SDL.h"

class SDL2Renderer : public IRenderer
{
public:
	SDL2Renderer(const char* _title, const int _width, const int _height);
	~SDL2Renderer() override;

	void clear() override;
	void draw() override;
	void swap() override;

	SDL_Window* getWindow() override { return m_pWindow; }

private:
	SDL_Window* m_pWindow;
	SDL_Renderer * m_pRenderer;
};