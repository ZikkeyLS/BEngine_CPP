#include "ScriptEngine.h"
#include "ScriptGlue.h"

namespace BEngine {

	namespace Utils {

		char* ReadBytes(const std::filesystem::path& filepath, uint32_t* outSize)
		{
			std::ifstream stream(filepath, std::ios::binary | std::ios::ate);

			if (!stream)
			{
				// Failed to open the file
				return nullptr;
			}

			std::streampos end = stream.tellg();
			stream.seekg(0, std::ios::beg);
			uint64_t size = end - stream.tellg();

			if (size == 0)
			{
				// File is empty
				return nullptr;
			}

			char* buffer = new char[size];
			stream.read((char*)buffer, size);
			stream.close();

			*outSize = (uint32_t)size;
			return buffer;
		}

		MonoAssembly* LoadMonoAssembly(const std::filesystem::path& assemblyPath)
		{
			uint32_t fileSize = 0;
			char* fileData = ReadBytes(assemblyPath, &fileSize);

			// NOTE: We can't use this image for anything other than loading the assembly because this image doesn't have a reference to the assembly
			MonoImageOpenStatus status;
			MonoImage* image = mono_image_open_from_data_full(fileData, fileSize, 1, &status, 0);

			if (status != MONO_IMAGE_OK)
			{
				const char* errorMessage = mono_image_strerror(status);
				// Log some error message using the errorMessage data
				return nullptr;
			}

			std::string path = assemblyPath.string();
			MonoAssembly* assembly = mono_assembly_load_from_full(image, path.c_str(), &status, 0);
			mono_image_close(image);

			BE_INFO("Welcome!");
			// Don't forget to free the file data
			delete[] fileData;

			return assembly;
		}

		void PrintAssemblyTypes(MonoAssembly* assembly)
		{
			MonoImage* image = mono_assembly_get_image(assembly);
			const MonoTableInfo* typeDefinitionsTable = mono_image_get_table_info(image, MONO_TABLE_TYPEDEF);
			int32_t numTypes = mono_table_info_get_rows(typeDefinitionsTable);

			for (int32_t i = 0; i < numTypes; i++)
			{
				uint32_t cols[MONO_TYPEDEF_SIZE];
				mono_metadata_decode_row(typeDefinitionsTable, i, cols, MONO_TYPEDEF_SIZE);

				const char* nameSpace = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAMESPACE]);
				const char* name = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAME]);

				MonoClass* monoClass = mono_class_from_name(image, nameSpace, name);
				printf("%s.%s\n", nameSpace, name);
			}
		}
	}

	struct ScriptEngineData {
		MonoDomain* RootDomain = nullptr;
		MonoDomain* AppDomain = nullptr;

		MonoAssembly* CoreAssembly = nullptr;
		MonoImage* CoreAssemblyImage = nullptr;

		ScriptClass EntityClass;

		std::unordered_map<std::string, Ref<ScriptClass>> EntityClasses;
	};

	static ScriptEngineData* s_Data;

	void ScriptEngine::Initialize()
	{
		s_Data = new ScriptEngineData();

		InitializeMono();
		LoadAssembly("BEngineScriptCore.dll");
		LoadAssemblyClasses(s_Data->CoreAssembly);

		ScriptGlue::Register();


		//MonoObject* instance = s_Data->EntityClass.Instantiate();
		//MonoMethod* printVector = s_Data->EntityClass.GetMethod("PrintVector", 0);
		//s_Data->EntityClass.Invoke(instance, printVector, nullptr);
	}

	void ScriptEngine::Shutdown()
	{
		ShutdownMono();
		delete s_Data;
	}

	void ScriptEngine::InitializeMono()
	{
		mono_set_assemblies_path("libs");

		MonoDomain* rootDomain = mono_jit_init("BEngineJITRuntime");

		if (rootDomain == nullptr) {
			return;
		}

		s_Data->RootDomain = rootDomain;
	}

	void ScriptEngine::LoadAssemblyClasses(MonoAssembly* assembly)
	{
		s_Data->EntityClasses.clear();

		MonoImage* image = mono_assembly_get_image(assembly);
		const MonoTableInfo* typeDefinitionsTable = mono_image_get_table_info(image, MONO_TABLE_TYPEDEF);
		int32_t numTypes = mono_table_info_get_rows(typeDefinitionsTable);

		s_Data->EntityClass = ScriptClass("BEngine", "Entity");

		for (int32_t i = 0; i < numTypes; i++)
		{
			uint32_t cols[MONO_TYPEDEF_SIZE];
			mono_metadata_decode_row(typeDefinitionsTable, i, cols, MONO_TYPEDEF_SIZE);

			const char* nameSpace = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAMESPACE]);
			const char* name = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAME]);

			MonoClass* monoClass = mono_class_from_name(image, nameSpace, name);

			if (monoClass == s_Data->EntityClass.AsRaw())
				continue;

			bool isEntity = mono_class_is_subclass_of(monoClass, s_Data->EntityClass.AsRaw(), false);

			if (isEntity) 
			{
				std::string fullName = strlen(nameSpace) != 0 ? fmt::format("{}.{}", nameSpace, name) : name;
				s_Data->EntityClasses[fullName] = CreateRef<ScriptClass>(nameSpace, name);
			}

			printf("%s.%s.%s\n", nameSpace, name, isEntity ? "true" : "false");
		}
	}

	void ScriptEngine::ShutdownMono()
	{
		mono_domain_unload(s_Data->AppDomain);
		s_Data->AppDomain = nullptr;

		mono_jit_cleanup(s_Data->RootDomain);
		s_Data->RootDomain = nullptr;
	}

	void ScriptEngine::LoadAssembly(const std::filesystem::path& filepath)
	{
		s_Data->AppDomain = mono_domain_create_appdomain("BEngineScriptRuntime", nullptr);
		mono_domain_set(s_Data->AppDomain, true);

		s_Data->CoreAssembly = Utils::LoadMonoAssembly(filepath);
		s_Data->CoreAssemblyImage = mono_assembly_get_image(s_Data->CoreAssembly);

		// PrintAssemblyTypes(s_Data->CoreAssembly);
	}

	std::unordered_map<std::string, Ref<ScriptClass>> ScriptEngine::GetEntityClasses()
	{
		return s_Data->EntityClasses;
	}

	MonoObject* ScriptEngine::InstantiateClass(MonoClass* monoClass)
	{
		MonoObject* instance = mono_object_new(s_Data->AppDomain, monoClass);
		mono_runtime_object_init(instance);
		return instance;
	}


	ScriptClass::ScriptClass(const std::string& classNamespace, const std::string& className)
		: m_Namespace(classNamespace), m_Name(className)
	{
		m_MonoClass = mono_class_from_name(s_Data->CoreAssemblyImage, classNamespace.c_str(), className.c_str());
	}

	MonoObject* ScriptClass::Instantiate()
	{
		return ScriptEngine::InstantiateClass(m_MonoClass);
	}

	MonoMethod* ScriptClass::GetMethod(const std::string& name, int parameterCount)
	{
		return mono_class_get_method_from_name(m_MonoClass, name.c_str(), parameterCount);
	}

	MonoObject* ScriptClass::Invoke(MonoObject* instance, MonoMethod* method, void** params = nullptr)
	{
		return mono_runtime_invoke(method, instance, params, nullptr);
	}

	ScriptInstance::ScriptInstance(Ref<ScriptClass> scriptClass) 
		: m_ScriptClass(scriptClass)
	{
		m_Instance = scriptClass->Instantiate();

		m_Create = scriptClass->GetMethod("Create", 0);
		m_Update = scriptClass->GetMethod("Update", 0);
	}

	void ScriptInstance::InvokeCreate()
	{
		m_ScriptClass->Invoke(m_Instance, m_Create);
	}

	void ScriptInstance::InvokeUpdate()
	{
		m_ScriptClass->Invoke(m_Instance, m_Update);
	}
}
