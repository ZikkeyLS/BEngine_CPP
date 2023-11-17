#include "ScriptLinker.h"

namespace BEngine {

#define BE_INTERNAL_CALL(Name) mono_add_internal_call("BEngine.InternalCalls::" #Name, Name)

	static void Log(MonoString* message)
	{
		BE_INFO("{}", mono_string_to_utf8(message));
	}

	void ScriptLinker::Register()
	{
		BE_INTERNAL_CALL(Log);
	}
}
