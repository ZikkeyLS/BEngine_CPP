project(imgui CXX)

file(GLOB imguiSources "*.cpp" "*.h")
add_library(imgui ${imguiSources})

target_include_directories(imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(imgui glfw)