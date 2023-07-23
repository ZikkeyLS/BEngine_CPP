#include "BEngineEditor.h"
#include "BEngine.h"
#include <filesystem>

using namespace std;

int main()
{
#ifndef NDEBUG
	std::filesystem::current_path("../Debug");
#endif

	cout << "Hello CMake." << endl;
	cout << BEngine::add(10220, 100) << endl;

	BEngine::test();
	BEngine::untest();
	return 0;
}
