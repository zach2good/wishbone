#pragma once

#include "IRenderer.h"

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

class OpenGLRenderer : public IRenderer {
public:
  OpenGLRenderer(const char *_title, const int _width, const int _height);
  ~OpenGLRenderer() override;

  void clear() override;
  void drawDebug();
  void submit(World* _world) override;
  void draw() override;
  void swap() override;

  void setResourceManager(ResourceManager* rm);
  
  void drawSprite(GameObject *go, Sprite *sp);

  SDL_Window *getWindow() override { return m_pWindow; }

  bool isActive;

private:
  SDL_Window *m_pWindow;
  SDL_GLContext m_GLContext;

  ResourceManager* rm;
  World* m_World;
  Shader *spriteShader;

  GLuint VAO, VBO;

  ResourceManager* m_ResourceManager;
  
  ImColor m_clearColor;
};
