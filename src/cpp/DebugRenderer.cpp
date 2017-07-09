#include "DebugRenderer.h"

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
#include "Player.h"
#include "World.h"
#include "Timer.h"
#include "OpenGLRenderer.h"
#include "Physics.h"

DebugRenderer::DebugRenderer(SDL_Window* window)
{
	m_pWindow = window;
	ImGuiIO &io = ImGui::GetIO();
	io.IniFilename = NULL; // Disables ini file output
	ImGui_ImplSdlGL3_Init(m_pWindow);
}

DebugRenderer::~DebugRenderer()
{
	ImGui_ImplSdlGL3_Shutdown();
}

void DebugRenderer::submit(ResourceManager* _rm, OpenGLRenderer* _renderer, World* _world)
{
	rm = _rm;
	m_Renderer = _renderer;
	m_World = _world;
}

void DebugRenderer::clear()
{
	ImGui_ImplSdlGL3_NewFrame(m_pWindow);
}

void DebugRenderer::draw()
{
	auto timer = TimerSingleton::Instance();
	timer->profile("Debug draw start");

	auto in = InputManagerSingleton::Instance();

	ImGui::SetNextWindowPos(ImVec2(10, 10), 0);

	if (ImGui::CollapsingHeader("Instructions##Main")) {
		ImGui::TextWrapped("Controls:");
		ImGui::TextWrapped("WASD - Movement");
		ImGui::TextWrapped("Z - Celebrate");
		ImGui::TextWrapped("X - Play Dead");
		ImGui::TextWrapped("ESC - Quit");
	}

	if (ImGui::CollapsingHeader("Options##Main")) {
		ImGui::Checkbox("Renderer##CheckBox1", &m_Renderer->isActive);  ImGui::SameLine(150); ImGui::Checkbox("World##CheckBox2", &m_World->isActive);
		ImGui::DragFloat("Time Multiplier", &timer->multiplier, 0.01f, 0.01f, 20.0f);
		ImGui::DragFloat("Gravity", &m_World->gravity, 0.001f, 0.001f, 20.0f);
	}

	if (ImGui::CollapsingHeader("Renderer")) {
		static ImVector<float> values;
		values.push_back(ImGui::GetIO().Framerate);
		if (values.size() > 100)
		{
			values.erase(values.begin());
		}
		float arr[100];
		std::copy(values.begin(), values.end(), arr);

		ImGui::Text("%.3f ms/frame | %.1f FPS", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		if (values.empty()) { values.resize(90); memset(values.Data, 0, values.Size * sizeof(float)); }
		static int values_offset = 0;
		ImGui::PlotLines("##Lines", values.Data, values.Size, values_offset, "", -1.0f, 100.0f, ImVec2(0, 80));

		ImGui::Text("Clear Colour");
		ImGui::ColorEdit3("Clear Colour", (float*)&m_Renderer->m_clearColor);
		if (ImGui::TreeNode("OpenGL Information")) {
			ImGui::TextWrapped("GL_VERSION: %s \n", glGetString(GL_VERSION));
			ImGui::TextWrapped("GL_VENDOR: %s \n", glGetString(GL_VENDOR));
			ImGui::TextWrapped("GL_SHADING_LANGUAGE_VERSION: %s \n",
				glGetString(GL_SHADING_LANGUAGE_VERSION));
			ImGui::TreePop();
		}
	}
	if (ImGui::CollapsingHeader("GameObjects##GO")) {
		for (int i = 0; i < m_World->m_gameObjects.size(); ++i) {
			auto go = m_World->m_gameObjects.at(i);
			if (!go) return;

			auto title = std::string("[" + std::to_string(i) + "] " + go->name);
			if (ImGui::TreeNode(title.c_str())) {
				ImGui::Text("Basic");
				ImGui::Text("X:%.0f Y:%.0f", go->x, go->y);

				for (int j = 0; j < go->m_Components.size(); j++) {
					auto comp = go->m_Components[j];
					if (!comp) return;

					if (comp->IsOfType<Sprite*>()) {
						auto sprite = static_cast<Sprite*>(comp);
						ImGui::Text("Sprite");
						ImGui::Text("W:%.0f H:%.0f", sprite->w, sprite->h);
					}
					else if (comp->IsOfType<AnimatedSprite*>()) {
						auto anim_sprite = static_cast<AnimatedSprite*>(comp);
						auto sprite = anim_sprite->frames.at(anim_sprite->currentFrame);
						ImGui::Text("AnimatedSprite");
						ImGui::Text("Frames:"); ImGui::SameLine();
						ImGui::Text("%d/%d", anim_sprite->currentFrame, anim_sprite->frames.size());
					}
					else if (comp->IsOfType<Player*>()) {
						auto player = static_cast<Player*>(comp);
						ImGui::Text("Player");
						ImGui::Text("State: %s", player->getStateString());
					}
                    else if (comp->IsOfType<Physics*>())
                    {
                        auto phys = static_cast<Physics*>(comp);
                        ImGui::Text("Physics");
                        ImGui::Text("dx:%.0f, dy:%.0f", phys->dx, phys->dy);
                    }
				}
				ImGui::TreePop();
			}
		}
	}

	if (ImGui::CollapsingHeader("Textures")) {
		for (auto &tex : rm->m_mapTextures) {
			auto t = tex.second;
			if (ImGui::TreeNode(tex.first.c_str())) {
				double multiplier = 250.0 / t->width;
				ImVec2 v(t->width * multiplier, t->height * multiplier);
				ImGui::Image((void *)(GLuint)t->ID, v);
				ImGui::TreePop();
			}
		}
	}

	if (ImGui::CollapsingHeader("Input")) {
		for (int i = 0; i < in->keyState.size(); i++) {
			if (i % 20 == 0) ImGui::NewLine();
			ImGui::Text("%s", (in->keyState[i]?"X":"_")); ImGui::SameLine();
		}
	}

	if (ImGui::CollapsingHeader("Player")) {
		Player* player = nullptr;
		for (int i = 0; i < m_World->m_gameObjects.size(); ++i) {
			auto go = m_World->m_gameObjects.at(i);
			if (!go) return;
			for (int j = 0; j < go->m_Components.size(); j++) {
				auto comp = go->m_Components[j];
				if (!comp) return;
				else if (comp->IsOfType<Player>()) {
					player = static_cast<Player *>(comp);
				}
			}
		}
		ImGui::Text("State: %s", player->getStateString());
		ImGui::Text("Health: %i", player->health);
		ImGui::Checkbox("isOnGround", &player->isOnGround);
		ImGui::Checkbox("isPushingCeiling", &player->isPushingCeiling);
		ImGui::Checkbox("isPushingLeftWall", &player->isPushingLeftWall);
		ImGui::Checkbox("isPushingRightWall", &player->isPushingRightWall);
		ImGui::DragFloat("walkSpeed", &player->walkSpeed, 0.1, 0, 20);
		ImGui::DragFloat("jumpPower", &player->jumpPower, 0.1, 0, 20);
	}

	if (ImGui::CollapsingHeader("Physics")) {
		for (int i = 0; i < m_World->physicsItems.size(); i++)
		{
			//ImGui::Text("%s: %s", m_World->physicsItems[i]->parent->name.c_str(), m_World->physicsItems[i]->isColliding? "Yes" : "No");
		}
		
	}
}

void DebugRenderer::swap()
{
	ImGui::Render();
}
