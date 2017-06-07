#include "SDL2Renderer.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

SDL2Renderer::SDL2Renderer(const char* _title, const int _width, const int _height)
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
		SDL_WINDOW_SHOWN);

	if (!m_pWindow) {
		std::cout << "Window Error" << std::endl;
	}

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetWindowTitle(m_pWindow, "Wishbone");

	loadTexture("res/font_source2.png", "font");
	loadTexture("res/jetroid-sprites/player/idle/s01.png", "idle01");
}

SDL2Renderer::~SDL2Renderer()
{
	// Destroy Textures
	//SDL_DestroyTexture();

	// Destroy Surfaces
	//SDL_FreeSurface();

	// Destroy Objects
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
}

void SDL2Renderer::clear(float _r, float _g, float _b)
{
	SDL_SetRenderDrawColor(m_pRenderer, (Uint8) 255.0f * _r, (Uint8) 255.0f * _g, (Uint8) 255.0f * _b, 255);
	SDL_RenderClear(m_pRenderer);
}

void SDL2Renderer::draw()
{
	SDL_Rect dest;
	dest.x = 10;
	dest.y = 10;
	dest.w = 32;
	dest.h = 32;
	SDL_RenderCopy(m_pRenderer, m_mapTextures["idle01"], NULL, &dest);
}

void SDL2Renderer::swap()
{
	SDL_RenderPresent(m_pRenderer);
}

SDL_Surface* SDL2Renderer::loadSurface(const std::string& filepath, const std::string& name)
{
	if (m_mapSurfaces.count(name) != 0) {
		return m_mapSurfaces[name];
	}

	// Read data
	int width, height, bytesPerPixel;
	void* data = stbi_load(filepath.c_str(), &width, &height, &bytesPerPixel, 0);

	// Calculate pitch
	int pitch;
	pitch = width * bytesPerPixel;
	pitch = (pitch + 3) & ~3;

	// Setup relevance bitmask
	int Rmask, Gmask, Bmask, Amask;
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
	Rmask = 0x000000FF;
	Gmask = 0x0000FF00;
	Bmask = 0x00FF0000;
	Amask = (bytesPerPixel == 4) ? 0xFF000000 : 0;
#else
	int s = (bytesPerPixel == 4) ? 0 : 8;
	Rmask = 0xFF000000 >> s;
	Gmask = 0x00FF0000 >> s;
	Bmask = 0x0000FF00 >> s;
	Amask = 0x000000FF >> s;
#endif
	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(data, width, height, bytesPerPixel * 8,
		pitch, Rmask, Gmask,
		Bmask, Amask);

	if (!surface)
	{
		return nullptr;
	}

	m_mapSurfaces[name] = surface;

	return m_mapSurfaces[name];
}

SDL_Texture* SDL2Renderer::loadTexture(const std::string& filepath, const std::string& name)
{
	if (m_mapTextures.count(name) != 0) {
		return m_mapTextures[name];
	}

	SDL_Texture* texture = NULL;
	texture = SDL_CreateTextureFromSurface(m_pRenderer, loadSurface(filepath, name));

	m_mapTextures[name] = texture;

	return m_mapTextures[name];
}