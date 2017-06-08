#include "common.h"

#ifdef __linux
#  define SDL2_RENDERER
#endif 

#ifdef SDL2_RENDERER 
#  include "SDL2Renderer.h"
#  define REN SDL2Renderer 
#else
#  include "OpenGLRenderer.h"
#  define REN OpenGLRenderer
#endif

#include "common.h"

int main(int argc, char* argv[])
{
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;

	std::shared_ptr<REN> p = std::make_shared<REN>("Wishbone", 800, 600);
	auto m_Renderer = p.get();

	std::vector<GameObject*> gameObjects;

	GameObject go("player", 20, 20);
	Sprite sp("res/jetroid-sprites/player/idle/s01.png", "idle01");
	go.m_Components.push_back(&sp);

	GameObject go1("player", 50, 20);
	Sprite sp2("res/jetroid-sprites/player/idle/s03.png", "idle03");
	go1.m_Components.push_back(&sp2);

	gameObjects.push_back(&go);
	gameObjects.push_back(&go1);

	bool quit = false;
	SDL_Event event;
	while (!quit) {
		// Delta 
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		deltaTime = ((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
		if (deltaTime > 1000.0)
		{
			// Artificially large delta, clamp back to 16
			deltaTime = 16.0;
		}

		// Input
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
			{
				quit = true;
				break;
			}
			case SDL_KEYDOWN:
			  if (event.key.keysym.sym == SDLK_ESCAPE)
			    {
			      quit = true;
			    }
			  if (event.key.keysym.sym == SDLK_d)
			    {
				  go.x += 10;
			    }	  
			}
		}

		m_Renderer->submit(&gameObjects);

		m_Renderer->clear(0.3f, 0.3f, 0.3f);

		m_Renderer->draw();

		m_Renderer->swap();
	}

	return 0;
}
