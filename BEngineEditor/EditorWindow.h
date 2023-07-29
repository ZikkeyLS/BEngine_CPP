#pragma once
#include "Window.h"
#include "FrameBuffer.h"

namespace BEngineEditor
{
	class EditorWindow : public BEngine::Window
	{
	public:

	protected:
		virtual void OnInitialize() override;
		virtual void OnStart() override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;
	private:
		FrameBuffer* sceneBuffer;
	};
}
