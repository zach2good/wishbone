#include "OpenGLRenderer.h"

#include <iostream>

#include "imgui.h"
#include "imgui_impl_sdl_gl3.h"

#include "ResourceManager.h"
#include "AnimatedSprite.h"
#include "Component.h"
#include "GameObject.h"
#include "Shader.h"
#include "Sprite.h"
#include "Texture.h"

#include "World.h"

OpenGLRenderer::OpenGLRenderer(const char *_title, const int _width,
    const int _height) {
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

    // Start OpenGL Context
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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ImGuiIO &io = ImGui::GetIO();
    io.IniFilename = NULL; // Disables ini file output
    ImGui_ImplSdlGL3_Init(m_pWindow);

    m_clearColor = ImColor(50, 50, 50);

    glm::mat4 projection =
        glm::ortho(0.0f, static_cast<GLfloat>(_width),
            static_cast<GLfloat>(_height), 0.0f, -1.0f, 1.0f);

    // VS
    //spriteShader->Use().SetMatrix4("projection", projection);

    // FS
    //spriteShader->Use().SetInteger("image", 0);

    // TODO: Get from ResourceManager
    // loadTexture("res/graphics/player.png", "player");
    //loadTexture("res/graphics/enemies.png", "enemies");
    //loadTexture("res/graphics/tiles.png", "tiles");

    // Configure VAO/VBO
    GLuint VBO;
    GLfloat vertices[] = {
        // Pos      // Tex
        0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f };

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat),
        (GLvoid *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    isActive = true;
}

OpenGLRenderer::~OpenGLRenderer() {
    ImGui_ImplSdlGL3_Shutdown();
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
    ImGui_ImplSdlGL3_NewFrame(m_pWindow);
}

void OpenGLRenderer::setResourceManager(ResourceManager* rm)
{
    m_ResourceManager = rm;
}

void OpenGLRenderer::drawDebug() {

    ResourceManager* rm = m_ResourceManager;
    //if (!rm) return;
    
    ImGui::SetNextWindowPos(ImVec2(10, 10), 0);

    if (ImGui::CollapsingHeader("Options##Main")) {
        ImGui::Checkbox("Renderer##CheckBox1", &isActive);  ImGui::SameLine(150); ImGui::Checkbox("World##CheckBox2", &m_World->isActive);
    }
    
    if (ImGui::CollapsingHeader("Renderer")) {
        ImGui::ColorEdit3("Clear Colour", (float*)&m_clearColor);
        if (ImGui::CollapsingHeader("OpenGL Information")) {
            ImGui::Text("GL_VERSION: %s \n", glGetString(GL_VERSION));
            ImGui::Text("GL_VENDOR: %s \n", glGetString(GL_VENDOR));
            ImGui::Text("GL_SHADING_LANGUAGE_VERSION: %s \n",
                glGetString(GL_SHADING_LANGUAGE_VERSION));
        }
    }
    // TODO: World / GO / Component breakdown and inspection

    // TODO: Menu to pull JSON world state into text editor, edit, then push back onto world

    // TODO: Query and get more opengGL information on the fly, VAOs, VBOs etc.
    // draw calls 
    
    if (ImGui::CollapsingHeader("Textures")) {
        for (auto &tex : rm->m_mapTextures) {
            auto t = tex.second;
            std::string title = std::to_string(t->ID) + " : " + t->filename;
            if (ImGui::CollapsingHeader(title.c_str())) {
                double multiplier = 250.0 / t->width;
                ImVec2 v(t->width * multiplier, t->height * multiplier);
                ImGui::Image((void *)(GLuint)t->ID, v);
            }
        }
    }
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
                auto sprite = static_cast<Sprite *>(comp);
                drawSprite(go, sprite);
            }
            else if (comp->type == "anim_sprite") {
                auto anim_sprite = static_cast<AnimatedSprite *>(comp);
                Sprite *sprite = anim_sprite->frames->at(anim_sprite->currentFrame);
                drawSprite(go, sprite);
            }
            else if (comp->type == "gui") {
                //===
            }
        }
    }
}

void OpenGLRenderer::drawSprite(GameObject *go, Sprite *sp) {

    // TODO: Set up sprite shader uniforms
    
    // if (!rm) return;
  glm::vec2 position = glm::vec2(go->x, go->y);
  glm::vec2 size = glm::vec2(sp->w, sp->h);
  GLfloat rotate = 0.0f;
  glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

  spriteShader->Use();
  glm::mat4 model;
  model = glm::translate(model, glm::vec3(position, 0.0f));

  model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
  model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
  model =
      glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

  model = glm::scale(model, glm::vec3(size, 1.0f));

  // VS
  spriteShader->SetMatrix4("model", model);

  glm::vec2 offset(4, 2);
  spriteShader->SetVector2f("offset", offset);

  // TODO: This is super broken, fix me
  
  float x = (sp->x * 0.25f);
  float y = 0; // (sp->position * 0.5f);
  glm::vec2 add(x, y);
  spriteShader->SetVector2f("add", add);

  // FS
  spriteShader->SetVector3f("spriteColor", color);

  // TODO: Is it ok to be binding different textures every time we see them? Should I just
  // bind everything at the start and keep track of which slot they were bound in?

  // OR create one giant spritesheet and only bind that one giant texture? Is that good?
  glActiveTexture(GL_TEXTURE0);
  sp->tex->Bind();

  glBindVertexArray(this->VAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);

}

void OpenGLRenderer::swap() {
    drawDebug();
    ImGui::Render();
    SDL_GL_SwapWindow(m_pWindow);
}
