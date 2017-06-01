#include "OpenGLRenderer.h"

#include <iostream>

#include "glad/glad.h"

OpenGLRenderer::OpenGLRenderer(const char* _title, const int _width, const int _height)
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
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (!m_pWindow) {
		std::cout << "Window Error" << std::endl;
	}

	// Start OpenGL Context
	m_pGLContext = SDL_GL_CreateContext(m_pWindow);
	if (!m_pGLContext) {
		std::cout << "Context Error" << std::endl;
	}

	if (!gladLoadGL()) {
		std::cout << "Something went wrong with glad!" << std::endl;
	}
}

OpenGLRenderer::~OpenGLRenderer()
{
	SDL_GL_DeleteContext(m_pGLContext);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void OpenGLRenderer::clear()
{
	glClearColor(0.2, 0.2, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::draw()
{
	//
}

void OpenGLRenderer::swap()
{
	SDL_GL_SwapWindow(m_pWindow);
}

