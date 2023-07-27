project(BEngineClient)

file(GLOB BEngineClientSources "*.cpp" "*.h")

add_library(BEngineClient SHARED ${BEngineClientSources})
target_link_libraries(BEngineClient BEngineCore)

set_target_properties(BEngineClient PROPERTIES
		      FOLDER "BEngine")
