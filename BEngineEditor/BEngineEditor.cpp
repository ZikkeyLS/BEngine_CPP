#include "BEngineEditor.h"
#include "BEngine.h"
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

	cout << "Hello CMake." << endl;
	cout << BEngine::add(10220, 100) << endl;

	BEngine::test();
	BEngine::untest();
	return 0;
}
