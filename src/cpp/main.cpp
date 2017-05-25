#include "common.h"

int main(int argc, char* argv[]) 
{ 
	int width, height, bpp;
	unsigned char* rgb = stbi_load("myimage.png", &width, &height, &bpp, 3);
	stbi_image_free(rgb);

	rang::init();
	std::cout << rang::bg::gray << rang::fg::black << "Wishbone" << std::endl << rang::style::reset;

	json j = {
		{ "pi", 3.141 },
		{ "happy", true },
		{ "name", "Niels" },
		{ "nothing", nullptr },
		{ "answer",{
			{ "everything", 42 }
		} },
		{ "list",{ 1, 0, 2 } },
		{ "object",{
			{ "currency", "USD" },
			{ "value", 42.99 }
		} }
	};
	std::cout << j.dump(4) << std::endl;

	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);

	//Start SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL Error" << std::endl;
	}

	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(0, &current);

	// Start a Window
	auto m_Window = SDL_CreateWindow("",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		800, 600,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (!m_Window) {
		std::cout << "Window Error" << std::endl;
	}

	// Start OpenGL Context
	auto m_Context = SDL_GL_CreateContext(m_Window);
	if (!m_Context) {
		std::cout << "Context Error" << std::endl;
	}

	if (!gladLoadGL()) {
		std::cout << "Something went wrong with glad!" << std::endl;
	}

	ImGui_ImplSdlGL3_Init(m_Window);
	
	bool quit = false;
	SDL_Event event;
	while (!quit){
		while (SDL_PollEvent(&event)) {
			ImGui_ImplSdlGL3_ProcessEvent(&event);
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
					break;
				default:
					break;
			}
		}
		ImVec4 clear_color = ImColor(114, 144, 154);
		ImGui_ImplSdlGL3_NewFrame(m_Window);

		{
			static float f = 0.0f;
			ImGui::Text("Hello, world!");
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
			ImGui::ColorEdit3("clear color", (float*)&clear_color);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}
			
		glClearColor(0.2, 0.2, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ImGui::Render();
		SDL_GL_SwapWindow(m_Window);
	}
		
	ImGui_ImplSdlGL3_Shutdown();
	SDL_GL_DeleteContext(m_Context);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();

	std::cout << "Press any key to exit..." << std::endl;
	getchar();
	return 0;
}
