﻿#include "BEngineEditor.h"
#include "BEngine.h"
#include <libloaderapi.h>

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	cout << BEngine::add(10220, 100) << endl;

	BEngine::test();
	return 0;
}
