project(BEngineEditor)

file(GLOB BEngineEditorSources "*.cpp" "*.h" "*.hpp")

add_executable(BEngineEditor ${BEngineEditorSources})
target_link_libraries(BEngineEditor PRIVATE BEngineCore)