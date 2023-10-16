#include "Graphics.h"

namespace BEngine {

#pragma region DX11
//WIP
	static int const NUM_BACK_BUFFERS = 3;

	void DX11Graphics::Initialize(SDL_Window* graphicsWindow)
	{
		Graphics::Initialize(graphicsWindow);

		SDL_SysWMinfo wmInfo;
		SDL_VERSION(&wmInfo.version);
		SDL_GetWindowWMInfo(window, &wmInfo);
		HWND hwnd = wmInfo.info.win.window;
	
		// Setup swap chain
		DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = hwnd;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.Windowed = true;

		auto result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE,
			nullptr, 0, nullptr, 0,
			D3D11_SDK_VERSION, &swapChainDesc,
			&swapChain, &device,
			nullptr, &deviceContext);

		ID3D11Texture2D* pBackBuffer = NULL;
		auto buffer = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		buffer = device->CreateRenderTargetView(pBackBuffer, NULL, &renderTargetView);
		pBackBuffer->Release();

		D3D11_VIEWPORT vp;
		vp.Width = (FLOAT)1280;
		vp.Height = (FLOAT)720;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;

		// Подключаем вьюпорт к контексту устройства
		deviceContext->RSSetViewports(1, &vp);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
#ifdef NDEBUG
		io.IniFilename = "BEngineEditorGUI.ini";
#endif
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		ImGui::StyleColorsDark();

		ImGui_ImplSDL2_InitForD3D(window);
		ImGui_ImplDX11_Init(device, deviceContext);
	}

	void DX11Graphics::Start()
	{

	}

	void DX11Graphics::Update()
	{
		// Просто очищаем задний буфер
		float ClearColor[4] = { 0.0f, 0.0f, 1.0f, 1.0f }; // красный, зеленый, синий, альфа-канал
		deviceContext->ClearRenderTargetView(renderTargetView, ClearColor);
	}

	void DX11Graphics::LateUpdate()
	{

		Graphics::LateUpdate();
	}

	void DX11Graphics::PreUI()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}

	void DX11Graphics::PostUI()
	{
		ImGui::Render();

		deviceContext->OMSetRenderTargets(1, &renderTargetView, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		swapChain->Present(0, 0);
	}

	void DX11Graphics::Destroy()
	{
	}
#pragma endregion

#pragma region DX12

	void DX12Graphics::Initialize(SDL_Window* graphicsWindow)
	{
		Graphics::Initialize(graphicsWindow);
	}

	void DX12Graphics::Start()
	{
	}

	void DX12Graphics::Update()
	{

	}
#pragma endregion

#pragma region OpenGL

	void OpenGLGraphics::Initialize(SDL_Window* graphicsWindow)
	{
		Graphics::Initialize(graphicsWindow);

		context = SDL_GL_CreateContext(window);

		if (!gladLoadGL())
		{
			BE_ERROR("Can't load GLAD!");
			return;
		}

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
#ifdef NDEBUG
		io.IniFilename = "BEngineEditorGUI.ini";
#endif
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		ImGui::StyleColorsDark();

		ImGui_ImplSDL2_InitForOpenGL(window, context);
		ImGui_ImplOpenGL3_Init("#version 460");
	}

	void OpenGLGraphics::Start()
	{

	}

	void OpenGLGraphics::Update()
	{
		for (int i = 0; i < contexts.size(); i++) {
			GraphicsContext* context = contexts[i];

			if (context->frameBuffer == nullptr)
				continue;

			context->frameBuffer->Bind();

			glClearColor(context->bufferColor.r, context->bufferColor.g, context->bufferColor.b, context->bufferColor.a);
			glClear(GL_COLOR_BUFFER_BIT);

			// draw context objects, skybox and etc...

			context->frameBuffer->Unbind();
		}
	}

	void OpenGLGraphics::LateUpdate()
	{

		Graphics::LateUpdate();
	}

	void OpenGLGraphics::PreUI()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}

	void OpenGLGraphics::PostUI()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void OpenGLGraphics::Destroy() 
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();

		SDL_GL_DeleteContext(context);
	}
#pragma endregion

#pragma region Vulkan

	void VulkanGraphics::Initialize(SDL_Window* graphicsWindow)
	{
		Graphics::Initialize(graphicsWindow);
	}

	void VulkanGraphics::Start()
	{
	}

	void VulkanGraphics::Update()
	{

	}
#pragma endregion

}