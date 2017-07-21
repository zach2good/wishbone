#include "OpenGLRenderer.h"

#include <iostream>

#include "ResourceManager.h"
#include "AnimatedSprite.h"
#include "Component.h"
#include "GameObject.h"
#include "Shader.h"
#include "Sprite.h"
#include "Texture.h"
#include "Player.h"
#include "World.h"
#include "Timer.h"
#include "Animator.h"
#include "Physics.h"

OpenGLRenderer::OpenGLRenderer(const char *_title, const int _width,
    const int _height) {

	m_Width = _width;
	m_Height = _height;

    // Start SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL Error" << std::endl;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    // Start a Window
    m_pWindow =
        SDL_CreateWindow(_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            _width, _height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!m_pWindow) {
        std::cout << "Window Error" << std::endl;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
    SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);

    // TODO: This is meant to disable VSync but it isn't working, the renderer is still
    // capping out at 16ms even when there is no load...
	SDL_GL_SetSwapInterval(1);

    m_GLContext = SDL_GL_CreateContext(m_pWindow);
    if (!m_GLContext) {
        std::cout << "Context Error" << std::endl;
    }

    if (!gladLoadGL()) {
        std::cout << "Something went wrong with glad!" << std::endl;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);

    std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GL_VENDOR: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "GL_SHADING_LANGUAGE_VERSION: "
        << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_SCISSOR_TEST);

	glViewport(0, 0, m_Width, m_Height);
}

OpenGLRenderer::~OpenGLRenderer() {
    SDL_GL_DeleteContext(m_GLContext);
    SDL_DestroyWindow(m_pWindow);
    SDL_Quit();
}

void OpenGLRenderer::submit(World* _world) {
    m_World = _world;
}

void OpenGLRenderer::clear() {
    glClearColor(m_clearColor.Value.x, m_clearColor.Value.y, m_clearColor.Value.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::init(ResourceManager* rm)
{
    this->rm = rm;
	m_clearColor = ImColor(180, 180, 180);
	spriteShader = rm->LoadShader("sprite", "res/shaders/sprite.vs", "res/shaders/sprite.fs");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(m_Width),
		static_cast<GLfloat>(m_Height), 0.0f, -1.0f, 1.0f);

	spriteShader->Use().SetInteger("image", 0);

	spriteShader->SetMatrix4("projection", projection);

	isActive = true;
}

void OpenGLRenderer::draw() {

    if (!isActive) return;

    /*for (int i = 0; i < m_World->m_gameObjects.size(); ++i) {
        auto go = m_World->m_gameObjects.at(i).get();

        for (int j = 0; j < go->m_Components.size(); j++) {
            auto comp = go->m_Components[j].get();
            if (!comp)
                return;
            if (comp->IsOfType<Sprite>()) {
                auto sprite = static_cast<Sprite*>(comp);
                drawSprite(go, sprite);
            }
            else if (comp->IsOfType<AnimatedSprite>()) {
                auto anim_sprite = static_cast<AnimatedSprite*>(comp);
                drawSprite(go, anim_sprite->frames.at(anim_sprite->currentFrame));
            }
			else if (comp->IsOfType<Animator>()) {
				auto animator = static_cast<Animator*>(comp);
				auto anim_sprite = animator->getState(animator->currentState);
				drawSprite(go, anim_sprite->frames.at(anim_sprite->currentFrame));
			}
			else if (comp->IsOfType<Physics>()) {
				auto phys = static_cast<Physics*>(comp);
				for (auto& col : phys->colliders)
				{
					drawSquare(glm::vec4(col.offset.x, 
										 col.offset.y,
										 col.offset.x + col.size.x,
										 col.offset.y + col.size.y));
				}
			}
        }
    }*/
}

void OpenGLRenderer::drawLine(int x1, int y1, int x2, int y2)
{
    // TODO: Maybe just with a fragment shader?
}

void OpenGLRenderer::drawLine(glm::vec2 p1, glm::vec2 p2)
{
	drawLine(p1.x, p1.y, p2.x, p2.y);
}

void OpenGLRenderer::drawSquare(glm::vec4 sq)
{
	drawLine(sq.x, sq.y, sq.z, sq.y);
	drawLine(sq.w, sq.y, sq.z, sq.w);
	drawLine(sq.z, sq.w, sq.x, sq.w);
	drawLine(sq.x, sq.w, sq.x, sq.y);
}

void OpenGLRenderer::drawSprite(GameObject* go, Sprite* sp)
{
	// ===
}

void OpenGLRenderer::swap() {
    SDL_GL_SwapWindow(m_pWindow);
}
