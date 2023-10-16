#pragma once
#include <FrameBuffer.h>
#include <glm/vec4.hpp>
#include <vector>
#include <SDL2/SDL_video.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_dx11.h>
#include <d3d11.h>
#include <dxgi1_2.h>
#include <imgui_impl_sdl2.h>
#include <BEngine.h>
#include <SDL2/SDL_syswm.h>

#pragma comment(lib,"d3d11.lib")

namespace BEngine 
{
	class GraphicsContext {
	public:
		FrameBuffer* frameBuffer = nullptr;
		glm::vec4 bufferColor = glm::vec4(0, 0, 0, 1);
		// objects to draw
	};

	class Graphics {
	public:
		virtual void Initialize(SDL_Window* graphicsWindow) 
		{ 
			window = graphicsWindow; 
			contexts = std::vector<GraphicsContext*>(); 
		}

		void AddGraphicsContext(GraphicsContext* context)
		{
			contexts.push_back(context);
		}

		virtual void Start() { }
		virtual void Update() { }
		virtual void LateUpdate() { SDL_GL_SwapWindow(window); }
		virtual void Destroy() { }
		virtual void PreUI() { }
		virtual void PostUI() { }
	protected:
		SDL_Window* window;
		std::vector<GraphicsContext*> contexts;
	};

	class DX11Graphics : public Graphics {
	public:
		virtual void Initialize(SDL_Window* graphicsWindow) override;
		virtual void Start() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void PreUI() override;
		virtual void PostUI() override;
		virtual void Destroy() override;
	private:
		IDXGISwapChain* swapChain;
		ID3D11Device* device;
		ID3D11DeviceContext* deviceContext;
		ID3D11RenderTargetView* renderTargetView = NULL;
	};

	class DX12Graphics : public Graphics {
	public:
		virtual void Initialize(SDL_Window* graphicsWindow) override;
		virtual void Start() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void PreUI() override;
		virtual void PostUI() override;
		virtual void Destroy() override;
	};

	class OpenGLGraphics : public Graphics {
	public:
		virtual void Initialize(SDL_Window* graphicsWindow) override;
		virtual void Start() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void PreUI() override;
		virtual void PostUI() override;
		virtual void Destroy() override;
	private:
		SDL_GLContext context;
	};

	class VulkanGraphics : public Graphics {
	public:
		virtual void Initialize(SDL_Window* graphicsWindow) override;
		virtual void Start() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void PreUI() override;
		virtual void PostUI() override;
		virtual void Destroy() override;
	};
}
