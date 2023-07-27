#include "BEngineEditor.h"
#include "Window.h"
#include "EditorWindow.h"
#include <filesystem>

#ifndef NDEBUG
#include <string>
#include <windows.h>

std::string getpath()
{
	char result[MAX_PATH];
	std::string path = std::string(result, GetModuleFileName(NULL, result, MAX_PATH));
	size_t pos = path.find_last_of("\\/");
	return (std::string::npos == pos) ? "" : path.substr(0, pos);
}
#endif

using namespace std;

int main()
{
#ifndef NDEBUG
	std::string path = getpath();
	if (std::filesystem::current_path() != path)
		std::filesystem::current_path(path);
#endif

	BEngine::Window window;
	window.Initialize(BEngine::WindowSize { 700, 700 }, "BEngine-Test");
	window.Run();

	BEngineEditor::EditorWindow editorWindow;
	editorWindow.Initialize(BEngine::WindowSize { 640, 480 }, "BEngine-Editor");
	editorWindow.Run();

	return 0;
}
