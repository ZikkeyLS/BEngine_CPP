#pragma once

namespace BEngine {
	class ScriptEngine {
	public:
		static void Initialize();
		static void Shutdown();
	private:
		static void InitMono();
		static void ShutdownMono();
	};
}