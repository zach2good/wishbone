#include "common.h"

#include "OpenGLRenderer.h"

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
#include "SoundManager.h"

int main(int argc, char* argv[])
{
	// Create
    std::unique_ptr<InputManager> ptr_im = std::make_unique<InputManager>();
    auto m_InputManager = ptr_im.get();

    std::unique_ptr<OpenGLRenderer> ptr_ren = std::make_unique<OpenGLRenderer>("Wishbone", 800, 600);
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

	//auto timer = TimerSingleton::Instance();
	//timer->setup();

	gSound.Init();

    // Loop Start
	double delta = 16.0;
	double accumulator = 0.0;
    bool quit = false;
	SDL_Event event;
    while (!quit) {
		m_DebugRenderer->submit(m_ResourceManager, m_Renderer, m_World);
		m_DebugRenderer->clear();
		//timer.startFrame();

        delta = gTimer.getDelta();
		accumulator += delta;

		while (SDL_PollEvent(&event)) {
			quit = gInput.handleEvent(event);
		}
		//timer.profile("InputManager->poll()");
	
		m_World->step(delta);

		if (accumulator > 16.0) {
			//m_World->step(delta);
			//accumulator = 0.0;
		}
        
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
