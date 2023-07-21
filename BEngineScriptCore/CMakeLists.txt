project(BEngineScriptCore LANGUAGES CSharp)

file(GLOB BEngineScriptCoreSources "*.cs")

add_library(BEngineScriptCore SHARED ${BEngineScriptCoreSources})

set_target_properties(BEngineScriptCore PROPERTIES
		      FOLDER "BEngine")

set_property(TARGET BEngineScriptCore PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.7.2")
set_property(TARGET BEngineScriptCore PROPERTY WIN64_EXECUTABLE TRUE)