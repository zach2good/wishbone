#include "OpenGLRenderer.h"

#include <iostream>

#include "imgui.h"
#include "imgui_impl_sdl_gl3.h"

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
	m_GLContext = SDL_GL_CreateContext(m_pWindow);
	if (!m_GLContext) {
		std::cout << "Context Error" << std::endl;
	}
#ifdef _WIN32
	if (!gladLoadGL()) {
		std::cout << "Something went wrong with glad!" << std::endl;
	}
#endif

	ImGui_ImplSdlGL3_Init(m_pWindow);
}

OpenGLRenderer::~OpenGLRenderer()
{
	ImGui_ImplSdlGL3_Shutdown();
	SDL_GL_DeleteContext(m_GLContext);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void OpenGLRenderer::clear()
{
	glClearColor(0.2, 0.2, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::drawDebug()
{
	ImGui::SetNextWindowPos(ImVec2(10, 10), 0);
	if (ImGui::CollapsingHeader("OpenGL Information"))
	{
		ImGui::Text("GL_VERSION: %s \n", glGetString(GL_VERSION));
		ImGui::Text("GL_VENDOR: %s \n", glGetString(GL_VENDOR));
		ImGui::Text("GL_SHADING_LANGUAGE_VERSION: %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	}
}

void OpenGLRenderer::draw()
{
	
}

void OpenGLRenderer::swap()
{
	ImGui_ImplSdlGL3_NewFrame(m_pWindow);
	drawDebug();
	ImGui::Render();
	SDL_GL_SwapWindow(m_pWindow);
}

