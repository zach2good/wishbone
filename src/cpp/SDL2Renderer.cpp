#include "SDL2Renderer.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"

SDL2Renderer::SDL2Renderer(const char* _title, const int _width, const int _height)
	: m_gameObjects(nullptr)
{
	//Start SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL Error" << std::endl;
	}

	// Start a Window
	m_pWindow = SDL_CreateWindow(_title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		_width, _height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if (!m_pWindow) {
		std::cout << "Window Error" << std::endl;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	// Start OpenGL Context
	m_GLContext = SDL_GL_CreateContext(m_pWindow);
	if (!m_GLContext) {
		std::cout << "Context Error" << std::endl;
	}

	if (!gladLoadGL()) {
		std::cout << "Something went wrong with glad!" << std::endl;
	}

	//direct3d, openGL, opengles2, opengles, software
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "openGL");

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_RendererInfo rendererInfo;
	SDL_GetRendererInfo(m_pRenderer, &rendererInfo);

	std::cout << "Renderer: " << rendererInfo.name << std::endl;
	std::cout << "CurrentVideoDriver: " << SDL_GetCurrentVideoDriver() << std::endl;
	std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GL_VENDOR: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "GL_SHADING_LANGUAGE_VERSION: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	
	SDL_SetWindowTitle(m_pWindow, "Wishbone");

	loadTexture("res/graphics/tiles.png", "tiles");
	loadTexture("res/graphics/player.png", "player");
	loadTexture("res/graphics/meter.png", "meter");
	loadTexture("res/graphics/enemies.png", "enemies");
	loadTexture("res/graphics/items.png", "items");
}

SDL2Renderer::~SDL2Renderer()
{
	// Destroy Textures
  for (auto& tex : m_mapTextures)
  {
		SDL_DestroyTexture(tex.second);
  }

  for (auto& surf : m_mapSurfaces)
	{
		SDL_FreeSurface(surf.second);
	}

	// Destroy Objects
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
}

void SDL2Renderer::submit(std::vector<GameObject*>* gameObjects)
{
	m_gameObjects = gameObjects;
}

void SDL2Renderer::clear(float _r, float _g, float _b)
{
	SDL_SetRenderDrawColor(m_pRenderer, (Uint8) 255.0f * _r, (Uint8) 255.0f * _g, (Uint8) 255.0f * _b, 255);
	SDL_RenderClear(m_pRenderer);
}

void SDL2Renderer::draw()
{
	for (int i = 0; i < m_gameObjects->size(); ++i)
	{
		auto go = m_gameObjects->at(i);
		if (!go) return;
		for (int j = 0; j < go->m_Components.size(); j++)
		{
			auto comp = go->m_Components[j];
			if (!comp) return;
			if (comp->type == "sprite")
			{
				auto sprite = static_cast<Sprite*>(comp);
				drawSprite(go, sprite);
			}
			else if (comp->type == "anim_sprite")
			{

			}
			else if (comp->type == "gui")
			{

			}
		}
	}
}

void SDL2Renderer::swap()
{
	SDL_RenderPresent(m_pRenderer);
}

void SDL2Renderer::drawSprite(GameObject* go, Sprite* sp)
{
	SDL_Rect dest;
	dest.x = go->x;
	dest.y = go->y;
	dest.w = 32;
	dest.h = 32;
	SDL_RenderCopy(m_pRenderer, m_mapTextures[sp->name], NULL, &dest);
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
