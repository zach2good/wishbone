#include "common.h"

#include "OpenGLRenderer.h"
#define REN OpenGLRenderer

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif


#include "ResourceManager.h"
#include "DebugRenderer.h"
#include "InputManager.h"

int main(int argc, char* argv[])
{
	// Create
    std::unique_ptr<InputManager> ptr_im = std::make_unique<InputManager>();
    auto m_InputManager = ptr_im.get();

    std::unique_ptr<REN> ptr_ren = std::make_unique<REN>("Wishbone", 800, 600);
    auto m_Renderer = ptr_ren.get();

    std::unique_ptr<ResourceManager> ptr_rm = std::make_unique<ResourceManager>();
    auto m_ResourceManager = ptr_rm.get();
    
    std::unique_ptr<World> ptr_wo = std::make_unique<World>();
    auto m_World = ptr_wo.get();

	std::unique_ptr<DebugRenderer> ptr_dr = std::make_unique<DebugRenderer>(m_Renderer->getWindow());
	auto m_DebugRenderer = ptr_dr.get();

	// Init
    m_Renderer->init(m_ResourceManager);
    m_World->init(m_ResourceManager);

	auto timer = TimerSingleton::Instance();
	timer->setup();

	auto in = InputManagerSingleton::Instance();
	SDL_Event event;

    // Loop Start
	double delta = 16.0;
    bool quit = false;
    while (!quit) {
		m_DebugRenderer->submit(m_ResourceManager, m_Renderer, m_World);
		m_DebugRenderer->clear();
		//timer.startFrame();

        delta = timer->getDelta();

		while (SDL_PollEvent(&event)) {
			quit = in->handleEvent(event);
		}
		//timer.profile("InputManager->poll()");

		
        m_World->step(delta);
		//timer.profile("World Step");

		
        m_Renderer->submit(m_World);
        m_Renderer->clear();
        m_Renderer->draw();
		//timer.profile("Renderer Draw");
		
		m_DebugRenderer->draw();
		m_DebugRenderer->swap();
		//timer.profile("Debug Draw");

        m_Renderer->swap();

		//timer.endFrame();
    }

    return 0;
}
