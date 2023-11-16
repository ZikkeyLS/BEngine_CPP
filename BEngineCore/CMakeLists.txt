project(BEngineCore CXX)

file(GLOB BEngineCoreSources "*.cpp" "*.h")
set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(BEngineCore STATIC ${BEngineCoreSources})

set_target_properties(BEngineCore PROPERTIES
		      FOLDER "BEngine")

set(core
	"BEngine.h")
source_group("Core" FILES ${core})

set(scripting
	"ScriptEngine.h" "ScriptEngine.cpp"
    "ScriptGlue.h" "ScriptGlue.cpp")
source_group("Scripting" FILES ${scripting})

set(graphics
	"Window.h" "Window.cpp"
    "Graphics.h" "Graphics.cpp"
	"FrameBuffer.h" "FrameBuffer.cpp")
source_group("Graphics" FILES ${graphics})

target_include_directories(BEngineCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

if (WIN32)
  target_link_libraries(BEngineCore PUBLIC "Ws2_32.lib")
  target_link_libraries(BEngineCore PUBLIC "Winmm.lib")
  target_link_libraries(BEngineCore PUBLIC "Version.lib")
  target_link_libraries(BEngineCore PUBLIC "Bcrypt.lib")
endif()

if (DEFINED DEBUG)
  target_link_directories(BEngineCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/mono/lib/Debug")
  target_link_libraries(BEngineCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/mono/lib/Debug/libmono-static-sgen.lib")

  target_link_directories(BEngineCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/sdl2/lib/Debug")
  target_link_libraries(BEngineCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/sdl2/lib/Debug/SDL2d.lib")
  target_link_libraries(BEngineCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/sdl2/lib/Debug/SDL2maind.lib")
else ()
  target_link_directories(BEngineCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/mono/lib/Release")
  target_link_libraries(BEngineCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/mono/lib/Release/libmono-static-sgen.lib")

  target_link_directories(BEngineCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/sdl2/lib/Release")
  target_link_libraries(BEngineCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/sdl2/lib/Release/SDL2.lib")
  target_link_libraries(BEngineCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/sdl2/lib/Release/SDL2main.lib")
endif ()

target_link_libraries(BEngineCore PUBLIC glad)
target_link_libraries(BEngineCore PUBLIC glm)
target_link_libraries(BEngineCore PUBLIC spdlog)
target_link_libraries(BEngineCore PUBLIC imgui)
