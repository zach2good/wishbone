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
	auto timer = Timer::getInstance();
	timer.profile("Debug draw start");

	ImGui::SetNextWindowPos(ImVec2(10, 10), 0);

	if (ImGui::CollapsingHeader("Options##Main")) {
		ImGui::Checkbox("Renderer##CheckBox1", &m_Renderer->isActive);  ImGui::SameLine(150); ImGui::Checkbox("World##CheckBox2", &m_World->isActive);
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

					if (comp->type == "sprite") {
						auto sprite = static_cast<Sprite *>(comp);
						ImGui::Text("Sprite");
						ImGui::Text("W:%.0f H:%.0f", sprite->w, sprite->h);
					}
					else if (comp->type == "anim_sprite") {
						auto anim_sprite = static_cast<AnimatedSprite *>(comp);
						auto sprite = anim_sprite->frames.at(anim_sprite->currentFrame);
						ImGui::Text("AnimatedSprite");
						ImGui::Text("Frames:"); ImGui::SameLine();
						ImGui::Text("%d/%d", anim_sprite->currentFrame, anim_sprite->frames.size());
					}
					else if (comp->type == "player") {
						auto player = static_cast<Player *>(comp);
						ImGui::Text("Player");
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

	if (ImGui::CollapsingHeader("Profiler")) {
		auto currentTime = SDL_GetTicks();
		double lastTime;
		if (currentTime > lastTime + 1000) {
			lastTime = currentTime;
		}
		else
		{
			return;
		}

		auto stamps = timer.current_timestamps;
		if (stamps->size() == 0) {
			ImGui::Text("No Stamps!");
			return;
		}

		auto start_time = stamps->at(0).second;
		auto end_time = stamps->at(stamps->size() - 1).second;
		auto frame_time = end_time - start_time;

		for (int i = 1; i < stamps->size(); i++)
		{
			auto previous = stamps->at(i - 1);
			auto current = stamps->at(i);
			auto time = current.second - previous.second;
			ImGui::Text("%s: %.0fns", std::string(current.first).c_str(), time);
			PlotVar("var" + i, time);
		}
		ImGui::Text("Frame Time: %.0fns", frame_time);
		PlotVar("ft", frame_time);
	}
}

void DebugRenderer::swap()
{
	ImGui::Render();
}

#include <vector>
#include <map>

struct PlotVarData
{
	ImGuiID        ID;
	std::vector<float>  Data;
	int            DataInsertIdx;
	int            LastFrame;

	PlotVarData() : ID(0), DataInsertIdx(0), LastFrame(-1) {}
};

typedef std::map<ImGuiID, PlotVarData> PlotVarsMap;
static PlotVarsMap	g_PlotVarsMap;

// Plot value over time
// Call with 'value == FLT_MAX' to draw without adding new value to the buffer
void DebugRenderer::PlotVar(const char* label, float value, float scale_min, float scale_max, size_t buffer_size)
{
	assert(label);
	if (buffer_size == 0)
		buffer_size = 120;

	ImGui::PushID(label);
	ImGuiID id = ImGui::GetID("");

	// Lookup O(log N)
	PlotVarData& pvd = g_PlotVarsMap[id];

	// Setup
	if (pvd.Data.capacity() != buffer_size)
	{
		pvd.Data.resize(buffer_size);
		memset(&pvd.Data[0], 0, sizeof(float) * buffer_size);
		pvd.DataInsertIdx = 0;
		pvd.LastFrame = -1;
	}

	// Insert (avoid unnecessary modulo operator)
	if (pvd.DataInsertIdx == buffer_size)
		pvd.DataInsertIdx = 0;
	int display_idx = pvd.DataInsertIdx;
	if (value != FLT_MAX)
		pvd.Data[pvd.DataInsertIdx++] = value;

	// Draw
	int current_frame = ImGui::GetFrameCount();
	if (pvd.LastFrame != current_frame)
	{
		ImGui::PlotLines("##plot", &pvd.Data[0], buffer_size, pvd.DataInsertIdx, NULL, scale_min, scale_max, ImVec2(0, 40));
		ImGui::SameLine();
		ImGui::Text("%s\n%-3.4f", label, pvd.Data[display_idx]/1000000.0f);	// Display last value in buffer
		pvd.LastFrame = current_frame;
	}

	ImGui::PopID();
}

void DebugRenderer::PlotVarFlushOldEntries()
{
	int current_frame = ImGui::GetFrameCount();
	for (PlotVarsMap::iterator it = g_PlotVarsMap.begin(); it != g_PlotVarsMap.end(); )
	{
		PlotVarData& pvd = it->second;
		if (pvd.LastFrame < current_frame - (int)pvd.Data.size())
			it = g_PlotVarsMap.erase(it);
		else
			++it;
	}
}
