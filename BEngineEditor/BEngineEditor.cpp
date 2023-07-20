#include "BEngineEditor.h"
#include "BEngine.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	cout << BEngine::add(10220, 100) << endl;

	BEngine::test();
	BEngine::untest();
	return 0;
}
