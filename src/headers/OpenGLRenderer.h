#pragma once

#include "IRenderer.h"
#include "SDL.h"

class OpenGLRenderer : public IRenderer
{
public:
	OpenGLRenderer(const char* _title, const int _width, const int _height);
	~OpenGLRenderer() override;

	void clear() override;
	void draw() override;
	void swap() override;

	SDL_Window* getWindow() override { return m_pWindow; }
	
private:
	SDL_Window* m_pWindow;
	SDL_GLContext m_pGLContext;
};