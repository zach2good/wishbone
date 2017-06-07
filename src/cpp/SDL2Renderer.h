#pragma once

#include "IRenderer.h"

#include <map>
#include <string>

class SDL2Renderer : public IRenderer
{
public:
	SDL2Renderer(const char* _title, const int _width, const int _height);
	~SDL2Renderer() override;

	void clear(float _r, float _g, float _b) override;
	void submit() override {};
	SDL_Surface* loadSurface(const std::string& filepath, const std::string& name);
	SDL_Texture* loadTexture(const std::string& filepath, const std::string& name);
	void draw() override;
	void swap() override;
	SDL_Window* getWindow() override { return m_pWindow; }

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	std::map<std::string, SDL_Surface*> m_mapSurfaces;
	std::map<std::string, SDL_Texture*> m_mapTextures;
};
