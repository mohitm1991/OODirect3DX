#include "Includes\BaseGame.h"

BaseGame::BaseGame() : device(nullptr), deviceContext(nullptr), swapChain(nullptr), backBuffer(nullptr)
{
}


BaseGame::~BaseGame()
{
	shutdown();
}

bool BaseGame::initialize(HINSTANCE instance, HWND window)
{
	this->instance = instance;
	this->window = window;

	RECT dimensions;
	GetClientRect(window, &dimensions);
	int width = dimensions.right - dimensions.left;
	int height = dimensions.bottom - dimensions.top;

	DXGI_SWAP_CHAIN_DESC swapChainDescriptor;
	ZeroMemory(&swapChainDescriptor, sizeof(swapChainDescriptor));
	swapChainDescriptor.BufferCount = 1;
	swapChainDescriptor.BufferDesc.Width = width;
	swapChainDescriptor.BufferDesc.Height = height;
	swapChainDescriptor.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDescriptor.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDescriptor.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDescriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDescriptor.OutputWindow = window;
	swapChainDescriptor.Windowed = TRUE;
	swapChainDescriptor.SampleDesc.Count = 1;
	swapChainDescriptor.SampleDesc.Quality = 0;

	HRESULT result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &swapChainDescriptor, &swapChain, &device, nullptr, &deviceContext);
	if(FAILED(result))
		return false;

	CComPtr<ID3D11Texture2D> backBufferTexture(nullptr);
	result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBufferTexture));
	if(FAILED(result))
		return false;

	result = device->CreateRenderTargetView(backBufferTexture, nullptr, &backBuffer);
	if(FAILED(result))
		return false;
	deviceContext->OMSetRenderTargets(1, &(backBuffer.p), nullptr);

	D3D11_VIEWPORT viewPort;
	viewPort.Width = static_cast<float>(width);
	viewPort.Height = static_cast<float>(height);
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	deviceContext->RSSetViewports(1, &viewPort);

	return loadContent();
}

void BaseGame::shutdown()
{
	unloadContent();

	backBuffer.Release();
	swapChain.Release();
	deviceContext.Release();
	device.Release();
}

bool BaseGame::loadContent()
{
	return true;
}

void BaseGame::unloadContent()
{
}