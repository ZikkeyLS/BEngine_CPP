#pragma once
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <wtypes.h>
#include <dxgi1_2.h>
#include <d3d11.h>

class FrameBuffer
{
public:
	FrameBuffer() { }
	FrameBuffer(float width, float height) { } 
	~FrameBuffer() { }
	virtual unsigned int getFrameTexture() { return 0; }
	virtual void RescaleFrameBuffer(float width, float height) { }
	virtual void Bind() const { }
	virtual void Unbind() const { }
};

class FrameBufferGL : public FrameBuffer
{
public:
	FrameBufferGL();
	FrameBufferGL(float width, float height);
	~FrameBufferGL();
	virtual unsigned int getFrameTexture() override;
	virtual void RescaleFrameBuffer(float width, float height) override;
	virtual void Bind() const override;
	virtual void Unbind() const override;
private:
	unsigned int fbo;
	unsigned int texture;
	unsigned int rbo;
};

class FrameBufferDX11 : public FrameBuffer
{
public:
	FrameBufferDX11();
	FrameBufferDX11(float width, float height);
	FrameBufferDX11(HWND hWindow);
	~FrameBufferDX11();
	virtual unsigned int getFrameTexture() override;
	virtual void RescaleFrameBuffer(float width, float height) override;
 	virtual void Bind() const override;
	virtual void Unbind() const override;
private:
	void createDevice(HWND window);
	void createRenderTarget();

	// Device stuff
	IDXGISwapChain* m_swapChain = nullptr;
	ID3D11Device* m_device = nullptr;
	ID3D11DeviceContext* m_deviceContext = nullptr;

	// Render target
	ID3D11RenderTargetView* m_renderTargetView = nullptr;
	D3D11_TEXTURE2D_DESC m_backBufferDesc;
};
