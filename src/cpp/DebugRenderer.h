#pragma once

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <glad/glad.h>

#include <map>
#include <string>

#include "imgui.h"
#include "ResourceManager.h"
#include "OpenGLRenderer.h"
#include "World.h"

class DebugRenderer {
public:
	DebugRenderer(SDL_Window* window);
   ~DebugRenderer();

  void submit(ResourceManager* _rm, OpenGLRenderer* _renderer, World* _world);
  void clear();
  void draw();
  void swap();

private:
	SDL_Window *m_pWindow;
	ResourceManager* rm;
	OpenGLRenderer* m_Renderer;
	World* m_World;
};
