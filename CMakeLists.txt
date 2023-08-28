cmake_minimum_required(VERSION 3.8)

project(BEngine)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(BEngineCore)
add_subdirectory(BEngineScriptCore)
add_subdirectory(BEngineClient)
add_subdirectory(BEngineEditor)

add_subdirectory(external/glad)
add_subdirectory(external/spdlog)
add_subdirectory(external/imgui)
add_subdirectory(external/glm)
