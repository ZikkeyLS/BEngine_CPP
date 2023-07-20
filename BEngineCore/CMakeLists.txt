project(BEngineCore CXX)

file(GLOB BEngineCoreSources "*.cpp" "*.h")
set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(BEngineCore SHARED ${BEngineCoreSources})
target_include_directories(BEngineCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(BEngineCore glad)
target_link_libraries(BEngineCore glfw)

set_target_properties(BEngineCore PROPERTIES
		      FOLDER "BEngine")