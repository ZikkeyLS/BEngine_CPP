project(BEngineScriptCore LANGUAGES CSharp)

add_library(BEngineScriptCore SHARED Main.cs)

set_property(TARGET BEngineScriptCore PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.7.2")
set_property(TARGET BEngineScriptCore PROPERTY WIN64_EXECUTABLE TRUE)