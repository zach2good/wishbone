#pragma once

#include "IRenderer.h"

class OpenGLRenderer : public IRenderer
{
public:
	OpenGLRenderer(const char* _title, const int _width, const int _height);
	~OpenGLRenderer() override;

	void clear() override;
	void drawDebug();
	void draw() override;
	void swap() override;

	SDL_Window* getWindow() override { return m_pWindow; }
	
private:
	SDL_Window* m_pWindow;
	SDL_GLContext m_GLContext;
};
