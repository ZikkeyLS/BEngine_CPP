#pragma once
#include <string>
#include <glad/glad.h>
#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

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
		int Initialize(const std::string& name, const WindowSize& size);
		void Run();
	protected:
		virtual void OnInitialize() { }
		virtual void OnStart() { }
		virtual void OnWindowEvent(SDL_Event* windowEvent) { }
		virtual void OnUpdate() { }
		virtual void OnDestroy() { }

		virtual SDL_Window* CreateWindow(const std::string& name, const WindowSize& size) 
		{ 
			return SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
				size.x, size.y, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
		}

		SDL_Window* window = nullptr;
		WindowSize size = WindowSize{ 0, 0 };
	private:

	};
}
