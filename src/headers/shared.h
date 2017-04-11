#pragma once

#include <iostream>
#include <string>
#include <string.h>
#include <iostream>
#include <ctime>
#include <iomanip>

#include "rang.hpp"

//#include "stb_image.h"
//#include "stb_easy_font.h"

//#include "vulkan/vulkan.h"

#ifdef __linux__ 
//linux code goes here

#elif _WIN32
// windows code goes here

#else
#error Platform not supported
#endif

static std::time_t time_now = std::time(nullptr);

#define LOG_ERROR(m) std::cout << rang::bg::red << std::put_time(std::localtime(&time_now), "%y-%m-%d %OH:%OM:%OS") << " [ERROR] " << "(" << __FUNCTION__ << ":" << __LINE__ << ") || " << m << rang::style::reset << std::endl;
#define LOG_WARN(m) std::cout << rang::bg::yellow << std::put_time(std::localtime(&time_now), "%y-%m-%d %OH:%OM:%OS") << " [WARN] " << "(" << __FUNCTION__ << ":" << __LINE__ << ") || " << m << rang::style::reset << std::endl;
#define LOG_INFO(m) std::cout << rang::bg::cyan << std::put_time(std::localtime(&time_now), "%y-%m-%d %OH:%OM:%OS") << " [INFO] " << "(" << __FUNCTION__ << ":" << __LINE__ << ") || " << m << rang::style::reset << std::endl;
#define LOG(m) std::cout << std::put_time(std::localtime(&time_now), "%y-%m-%d %OH:%OM:%OS") << " [LOG] " << "(" << __FUNCTION__ << ":" << __LINE__ << ") || " << m << rang::style::reset << std::endl;