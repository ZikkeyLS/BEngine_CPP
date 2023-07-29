#pragma once
#include <cstdint>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <FrameBuffer.h>

namespace BEngine
{
	struct WindowSize
	{
		uint32_t x;
		uint32_t y;
	};

	class Window
	{
	public:
		Window();
		int Initialize(WindowSize size, std::string name);
		void Run();
	protected:
		virtual void OnInitialize() { }
		virtual void OnStart() { }
		virtual void OnUpdate() { }
		virtual void OnDestroy() { }

		GLFWwindow* window = nullptr;
		WindowSize size = WindowSize{ 0, 0 };
	private:

	};
}
