#pragma once
#include "Window.h"
#include "ScriptEngine.h"
#include "FrameBuffer.h"
#include <Graphics.h>

using namespace BEngine;

namespace BEngineEditor
{
	class EditorWindow : public BEngine::Window
	{
	public:

	protected:
		virtual void OnInitialize() override;
		virtual void OnStart() override;
		virtual void OnWindowEvent(SDL_Event* windowEvent) override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;
		virtual SDL_Window* CreateWindowInstance(const std::string& name, const WindowSize& size) override;
	private:
		void OnGUI();

		void OnLoaderGUI();
		void OnProjectGUI();

		Graphics* graphics;
		FrameBuffer* gameBuffer;
		FrameBuffer* sceneBuffer;
	};
}
