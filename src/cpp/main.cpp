#include "common.h"

#include "OpenGLRenderer.h"
#define REN OpenGLRenderer

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#include "ResourceManager.h"

int main(int argc, char* argv[])
{
    std::unique_ptr<Timer> ptr_time = std::make_unique<Timer>();
    auto m_Timer = ptr_time.get();

    std::unique_ptr<InputManager> ptr_im = std::make_unique<InputManager>();
    auto m_InputManager = ptr_im.get();

    std::unique_ptr<REN> ptr_ren = std::make_unique<REN>("Wishbone", 800, 600);
    auto m_Renderer = ptr_ren.get();

    std::unique_ptr<ResourceManager> ptr_rm = std::make_unique<ResourceManager>();
    auto m_ResourceManager = ptr_rm.get();
    
    std::unique_ptr<World> ptr_wo = std::make_unique<World>();
    auto m_World = ptr_wo.get();

    m_Renderer->setResourceManager(m_ResourceManager);
    m_World->setResourceManager(m_ResourceManager);

    // TODO: Move setup into init methods? 
    // m_Renderer.init();
    // m_ResourceManager.init();
    // m_AudioPlayer.init();
    // m_World.init();

    double delta = 16.0;
    // Loop Start
    bool quit = false;
    while (!quit) {

        delta = m_Timer->getDelta();

        quit = m_InputManager->poll();

        m_World->step(delta);
        
        m_Renderer->submit(m_World);
        m_Renderer->clear();
        m_Renderer->draw();

        // Debug Draw

        m_Renderer->swap();
    }

    // Clean up

    return 0;
}
