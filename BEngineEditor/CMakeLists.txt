project(BEngineEditor)

file(GLOB BEngineEditorSources "*.cpp" "*.h" "*.hpp")

add_executable(BEngineEditor ${BEngineEditorSources})
target_link_libraries(BEngineEditor BEngineCore)

add_custom_command(TARGET BEngineEditor
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       $(SolutionDir)/../libraries $<TARGET_FILE_DIR:BEngineEditor>)

set_target_properties(BEngineEditor PROPERTIES
		      FOLDER "BEngine")