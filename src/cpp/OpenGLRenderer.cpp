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
	SDL_GL_SetSwapInterval(0);

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
	spriteShader = rm->GetShader("sprite");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(m_Width),
		static_cast<GLfloat>(m_Height), 0.0f, -1.0f, 1.0f);

	spriteShader->Use().SetInteger("image", 0);

	spriteShader->SetMatrix4("projection", projection);

	// Configure VAO/VBO
	GLuint VBO;
	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	isActive = true;
}

void OpenGLRenderer::draw() {

    if (!isActive) return;

    for (int i = 0; i < m_World->m_gameObjects.size(); ++i) {
        auto go = m_World->m_gameObjects.at(i);
        if (!go)
            return;

        for (int j = 0; j < go->m_Components.size(); j++) {
            auto comp = go->m_Components[j];
            if (!comp)
                return;
            if (comp->type == "sprite") {
                auto sprite = static_cast<Sprite*>(comp);
                drawSprite(go, sprite);
            }
            else if (comp->type == "anim_sprite") {
                auto anim_sprite = static_cast<AnimatedSprite*>(comp);
                drawSprite(go, anim_sprite->frames.at(anim_sprite->currentFrame));
            }
			else if (comp->type == "animator") {
				auto animator = static_cast<Animator*>(comp);
				auto anim_sprite = animator->getState(animator->currentState);
				drawSprite(go, anim_sprite->frames.at(anim_sprite->currentFrame));
			}

            // TODO: Shader effects, I imagine I won't be changing the vertex shader, only the fragment shader,
            // So these won't be that big of a deal

            // TODO: Particals, no idea how to do these, especially with the current crappy OpenGL implementation
        }
    }
}

void OpenGLRenderer::drawSprite(GameObject *go, Sprite *sp) {
	Physics* phys = nullptr;
	for (int j = 0; j < go->m_Components.size(); j++) {

		if (go->m_Components.at(j)->type == "physics") {
			phys = static_cast<Physics*>(go->m_Components.at(j));
		}
	}

	glm::vec2 position = glm::vec2(go->x, go->y);
	glm::vec2 size = glm::vec2(100, 100);
	GLfloat rotate = 0;
	glm::vec3 color = glm::vec3(1, 1, 1);
	glm::vec4 srcRect = glm::vec4(sp->x, sp->y, sp->w, sp->h);

	if (phys->isColliding) {
		color = glm::vec3(1, 0, 0);
	}

    // TODO: Figure out how to do horizontal and vertical flipping only using srcRect
    // Try not to touch the shaders (especially the fs)
	if (sp->flip)
	{
		srcRect.x *= -1.0f;
	}

	spriteShader->Use();

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(position, 0.0f)); 
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));

	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	spriteShader->SetMatrix4("model", model);
	spriteShader->SetVector3f("spriteColor", color);
	spriteShader->SetVector4f("srcRect", srcRect);

	// TODO: This is expensive, do some sorting and do this as little as possible
    // TODO: Also, implement a Z draw order so sprites can be sent ot the front or back
	glActiveTexture(GL_TEXTURE0);
	sp->tex->Bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void OpenGLRenderer::swap() {
    SDL_GL_SwapWindow(m_pWindow);
}
