#include "FrameBuffer.h"

#pragma region OpenGL

FrameBufferGL::FrameBufferGL()
{

}

FrameBufferGL::FrameBufferGL(float width, float height)
{
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

FrameBufferGL::~FrameBufferGL()
{
	glDeleteFramebuffers(1, &fbo);
	glDeleteTextures(1, &texture);
	glDeleteRenderbuffers(1, &rbo);
}

unsigned int FrameBufferGL::getFrameTexture()
{
	return texture;
}

void FrameBufferGL::RescaleFrameBuffer(float width, float height)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
}

void FrameBufferGL::Bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void FrameBufferGL::Unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

#pragma endregion

#pragma region DX11

FrameBufferDX11::FrameBufferDX11()
{

}

FrameBufferDX11::FrameBufferDX11(float width, float height)
{

}

FrameBufferDX11::FrameBufferDX11(HWND hWindow)
{
	createDevice(hWindow);
	createRenderTarget();
}

FrameBufferDX11::~FrameBufferDX11()
{

}

unsigned int FrameBufferDX11::getFrameTexture()
{

	ID3D11Texture2D* pTexture2D = NULL;
	D3D11_TEXTURE2D_DESC dec;

	HRESULT result;
	D3DX11_IMAGE_LOAD_INFO loadInfo;
	ZeroMemory(&loadInfo, sizeof(D3DX11_IMAGE_LOAD_INFO));
	loadInfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	loadInfo.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	loadInfo.MipLevels = D3DX11_DEFAULT; //At this time, the largest mipmaps layer will be generated. 
	loadInfo.MipFilter = D3DX11_FILTER_LINEAR;
	result = D3DX11CreateTextureFromFile(pD3dDevice, lpszFilePath, &loadInfo, NULL, (ID3D11Resource**)(&pTexture2D), NULL);
	pTexture2D->GetDesc(&dec);

	if (result != S_OK)
	{
		return NULL;
	}

	ID3D11ShaderResourceView* pFontTextureView = NULL;

	// Create texture view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = dec.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;
	pD3dDevice->CreateShaderResourceView(pTexture2D, &srvDesc, &pFontTextureView);


	return (unsigned int)pFontTextureView;
}

void FrameBufferDX11::RescaleFrameBuffer(float width, float height)
{

}

void FrameBufferDX11::Bind() const
{
	// Bind render target
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, nullptr);
	// Set viewport
	auto viewport = CD3D11_VIEWPORT(0.f, 0.f, (float)m_backBufferDesc.Width, (float)m_backBufferDesc.Height);
	m_deviceContext->RSSetViewports(1, &viewport);
	// Set the background color
	float clearColor[] = { .25f, .5f, 1, 1 };
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, clearColor);
}

void FrameBufferDX11::Unbind() const
{
	// Swap the buffer!
	m_swapChain->Present(0, 0);
}

void FrameBufferDX11::createDevice(HWND hWindow)
{
	// Define our swap chain
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWindow;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = true;

	// Create the swap chain, device and device context
	auto result = D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
		nullptr, 0, D3D11_SDK_VERSION,
		&swapChainDesc, &m_swapChain,
		&m_device, nullptr, &m_deviceContext);

	// Check for error
	if (result != S_OK) {
		MessageBox(nullptr, "Error creating DX11", "Error", MB_OK);
		exit(0);
	}
}

void FrameBufferDX11::createRenderTarget()
{
	ID3D11Texture2D* backBuffer;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView);

	backBuffer->GetDesc(&m_backBufferDesc);
	backBuffer->Release();
}

#pragma endregion
