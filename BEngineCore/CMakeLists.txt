project(BEngineCore)

file(GLOB BEngineCoreSources "*.cpp" "*.h")

add_library(BEngineCore ${BEngineCoreSources})
target_include_directories(BEngineCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(BEngineCore glad)
target_link_libraries(BEngineCore glfw)