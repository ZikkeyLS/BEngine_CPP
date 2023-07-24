#pragma once
#include <cassert>
#include "spdlog/spdlog.h"
#include "mono/jit/jit.h"
#include <ctime>
#include <iostream>
#include <filesystem>
#include "mono/jit/jit.h"
#include "mono/metadata/assembly.h"
#include <fstream>
#include <iostream>
#include "glm/vec3.hpp"

#define BE_ASSERT assert
#define BE_LOG( ... ) ::spdlog::log(__VA_ARGS__)
#define BE_INFO( ... ) ::spdlog::info(__VA_ARGS__)
#define BE_WARN( ... ) ::spdlog::warn(__VA_ARGS__)
#define BE_ERROR( ... ) ::spdlog::error(__VA_ARGS__)

namespace BEngine 
{
	int add(int a, int b);
	int test();
	void untest();
}