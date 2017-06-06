#include "common.h"
#include "OpenGLRenderer.h"

int main(int argc, char* argv[]) 
{ 
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;

	std::shared_ptr<IRenderer> p = std::make_shared<OpenGLRenderer>("Wishbone", 800, 600);
	auto m_Renderer = p.get();

	bool quit = false;
	SDL_Event event;
	while (!quit){
		// Delta 
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		deltaTime = ((NOW - LAST) * 1000 / (double) SDL_GetPerformanceFrequency());
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
						break;
					}	
				default:
					break;
			}
		}

		m_Renderer->clear();

		m_Renderer->draw();

		m_Renderer->swap();
	}

	return 0;
}
