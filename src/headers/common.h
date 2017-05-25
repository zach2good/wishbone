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