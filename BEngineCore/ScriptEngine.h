#pragma once
#include "BEngine.h"

namespace BEngine {

	class ScriptClass
	{
	public:
		ScriptClass() = default;
		ScriptClass(const std::string& classNamespace, const std::string& className);

		MonoObject* Instantiate();
		MonoMethod* GetMethod(const std::string& name, int parameterCount);
		MonoObject* Invoke(MonoObject* instance, MonoMethod* method, void** params);

		MonoClass* AsRaw()
		{
			return m_MonoClass;
		}
	private:
		std::string m_Namespace;
		std::string m_Name;

		MonoClass* m_MonoClass = nullptr;
	};

	class ScriptInstance
	{
	public:
		ScriptInstance(Ref<ScriptClass> scriptClass);

		void InvokeCreate();
		void InvokeUpdate();
	private:
		Ref<ScriptClass> m_ScriptClass;

		MonoObject* m_Instance = nullptr;
		MonoMethod* m_Create = nullptr;
		MonoMethod* m_Update = nullptr;
	};

	class ScriptEngine {
	public:
		static void Initialize();
		static void Shutdown();

		static void LoadAssembly(const std::filesystem::path& filepath);

		static std::unordered_map<std::string, Ref<ScriptClass>> GetEntityClasses();
	private:
		static void InitializeMono();
		static void LoadAssemblyClasses(MonoAssembly* assembly);
		static void ShutdownMono();

		static MonoObject* InstantiateClass(MonoClass* monoClass);

		friend class ScriptClass;
	};
}