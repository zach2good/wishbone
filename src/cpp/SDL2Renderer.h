#pragma once

#include "IRenderer.h"

#ifdef _WIN32
#include <SDL_image.h>
#include <SDL_TTF.h>
#else
//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_TTF.h>
#endif

#include <map>
#include <string>

class SDL2Renderer : public IRenderer
{
public:
	SDL2Renderer(const char* _title, const int _width, const int _height);
	~SDL2Renderer() override;

	void clear(float _r, float _g, float _b) override;
	void submit() override {};
	SDL_Surface* loadImage(const std::string &filepath);
	void draw() override;
	void swap() override;
	SDL_Window* getWindow() override { return m_pWindow; }

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	std::map<std::string, SDL_Surface*> m_mapSprites;
	
	//SDL_Surface* screenSurface;
	//SDL_Texture* textTexture;
	//SDL_Rect textRect;

	//TTF_Font* font;
	//SDL_Color textColor = { 255, 255, 255, 255 }; // white
	//SDL_Color backgroundColor = { 0, 0, 0, 255 }; // black
};
