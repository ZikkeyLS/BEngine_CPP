#pragma once
#include "BEngine.h"

namespace BEngine {
	class ScriptEngine {
	public:
		static void Initialize();
		static void Shutdown();

		static void LoadAssembly(const std::filesystem::path& filepath);
	private:
		static void InitializeMono();
		static void ShutdownMono();

		static MonoObject* InstantiateClass(MonoClass* monoClass);

		friend class ScriptClass;
	};

	class ScriptClass
	{
	public:
		ScriptClass() = default;
		ScriptClass(const std::string& classNamespace, const std::string& className);

		MonoObject* Instantiate();
		MonoMethod* GetMethod(const std::string& name, int parameterCount);
		MonoObject* Invoke(MonoObject* instance, MonoMethod* method, void** params);
	private:
		std::string m_Namespace;
		std::string m_Name;

		MonoClass* m_MonoClass = nullptr;
	};
}