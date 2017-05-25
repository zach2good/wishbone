#pragma once

#include <stdio.h>
#include <iostream>

//https://github.com/nothings/stb/blob/master/stb_image.h
// Defined in the build script
//#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h"

//https://github.com/agauniyal/rang
#include "rang.hpp"

//https://github.com/nlohmann/json/tree/master
#include "json.hpp"
using json = nlohmann::json;

//https://github.com/Dav1dde/glad
#include "glad/glad.h"

#include "SDL.h"

//https://github.com/ocornut/imgui
#include "imgui.h"
#include "imgui_impl_sdl_gl3.h"

//http://glm.g-truc.net/0.9.8/index.html
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective