#pragma once
#include "Window.h"

namespace BEngineEditor
{
	class EditorWindow : public BEngine::Window
	{
	public:

	protected:
		virtual void OnInitialize() override;
		virtual void OnStart() override;
		virtual void OnDestroy() override;
	};
}
