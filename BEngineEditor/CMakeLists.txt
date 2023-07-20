project(BEngineEditor)

file(GLOB BEngineEditorSources "*.cpp" "*.h" "*.hpp")

add_executable(BEngineEditor ${BEngineEditorSources})
target_link_libraries(BEngineEditor BEngineCore)

set_target_properties(BEngineEditor PROPERTIES
		      FOLDER "BEngine")