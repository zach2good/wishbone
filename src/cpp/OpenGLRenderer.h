#pragma once

#include "IRenderer.h"

class GameObject;
class Component;
class Sprite;
class AnimatedSprite;

class OpenGLRenderer : public IRenderer
{
public:
	OpenGLRenderer(const char* _title, const int _width, const int _height);
	~OpenGLRenderer() override;

	void clear(float _r, float _g, float _b) override;
	void drawDebug();
	void submit(std::vector<GameObject*>* gameObjects) override;
	void draw() override;
	void swap() override;

	//SDL_Texture* loadTexture(const std::string& filepath, const std::string& name);

	void drawSprite(GameObject* go, Sprite* sp);

	SDL_Window* getWindow() override { return m_pWindow; }

private:
	SDL_Window* m_pWindow;
	SDL_GLContext m_GLContext;

	std::vector<GameObject*>* m_gameObjects;
};
