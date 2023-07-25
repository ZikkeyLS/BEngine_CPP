project(BEngineCore CXX)

file(GLOB BEngineCoreSources "*.cpp" "*.h")
set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(BEngineCore SHARED ${BEngineCoreSources})

set_target_properties(BEngineCore PROPERTIES
		      FOLDER "BEngine")

target_include_directories(BEngineCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

if (WIN32)
  target_link_libraries(BEngineCore "Ws2_32.lib")
  target_link_libraries(BEngineCore "Winmm.lib")
  target_link_libraries(BEngineCore "Version.lib")
  target_link_libraries(BEngineCore "Bcrypt.lib")
endif()

if (DEFINED DEBUG)
  target_link_directories(BEngineCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/mono/lib/Debug")
  target_link_libraries(BEngineCore "${CMAKE_CURRENT_SOURCE_DIR}/mono/lib/Debug/libmono-static-sgen.lib")
else ()
  target_link_directories(BEngineCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/mono/lib/Release")
  target_link_libraries(BEngineCore "${CMAKE_CURRENT_SOURCE_DIR}/mono/lib/Release/libmono-static-sgen.lib")
endif ()

target_link_libraries(BEngineCore glad)
target_link_libraries(BEngineCore glfw)
target_link_libraries(BEngineCore glm)
target_link_libraries(BEngineCore spdlog)
target_link_libraries(BEngineCore imgui)