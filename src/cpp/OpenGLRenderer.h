#pragma once

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <glad/glad.h>

#include <glm/vec2.hpp> // glm::vec2

#include <map>
#include <string>

#include "imgui.h"

class ResourceManager;
class GameObject;
class Component;
class Sprite;
class AnimatedSprite;
class Shader;
class Texture;

class World;

class OpenGLRenderer {
public:
  OpenGLRenderer(const char *_title, const int _width, const int _height);
  ~OpenGLRenderer();

  void clear();
  void submit(World* _world);
  void draw();
  void swap();

  void init(ResourceManager* rm);
  
  void drawSprite(GameObject *go, Sprite *sp);

  void drawLine(int x1, int y1, int x2, int y2);
  void drawLine(glm::vec2 p1, glm::vec2 p2);
  void drawSquare(glm::vec4 sq);

  SDL_Window *getWindow() { return m_pWindow; }

  bool isActive;

  SDL_Window *m_pWindow;
  SDL_GLContext m_GLContext;

  int m_Width, m_Height;

  ResourceManager* rm;
  World* m_World;

  // OGL
  Shader* spriteShader;
  GLuint quadVAO;
  
  ImColor m_clearColor;


  // Line Renderer
  Shader* lineShader;
  GLuint vao;
  GLuint vbo;
  GLuint ebo;
};
