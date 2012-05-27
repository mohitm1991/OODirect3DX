#include "Includes\Device.h"
#include "Includes\DirectXException.h"

#include "Includes\BlendDescriptor.h"
#include "Includes\BlendState.h"
#include "Includes\Buffer.h"
#include "Includes\DeviceContext.h"
#include "Includes\InputElementDescriptor.h"
#include "Includes\InputLayout.h"
#include "Includes\PixelShader.h"
#include "Includes\Resource.h"
#include "Includes\RenderTargetView.h"
#include "Includes\SamplerDescriptor.h"
#include "Includes\SamplerState.h"
#include "Includes\ShaderResourceView.h"
#include "Includes\SwapChain.h"
#include "Includes\SwapChainDescriptor.h"
#include "Includes\VertexShader.h"

Device::Device(DeviceContext* deviceContext) : device(nullptr)
{
	HRESULT result = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &device, nullptr, &(deviceContext->deviceContext));
	if(FAILED(result))
		throw DirectXException("Exception while creating device!");
}

BlendState* Device::createBlendState(const BlendDescriptor& blendDescriptor)
{
	CComPtr<ID3D11BlendState> blendState;
	HRESULT result = device->CreateBlendState(&(blendDescriptor.descriptor), &blendState);
	if(FAILED(result))
		throw DirectXException("Exception while creating blend state!");
	return new BlendState(blendState);
}

Buffer* Device::createConstantBuffer(int bufferSize)
{
	D3D11_BUFFER_DESC descriptor;
	ZeroMemory(&descriptor, sizeof(descriptor));
	descriptor.Usage = D3D11_USAGE_DEFAULT;
	descriptor.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	descriptor.ByteWidth = bufferSize;

	CComPtr<ID3D11Buffer> buffer;
	device->CreateBuffer(&descriptor, nullptr, &buffer);
	return new Buffer(buffer);
}

InputLayout* Device::createInputLayout(const vector<InputElementDescriptor>& inputElements, const VertexShader* vertexShader) const
{
	ID3DBlob* compiledShader = vertexShader->compiledShaderData;
	CComPtr<ID3D11InputLayout> inputLayout(nullptr);

	vector<D3D11_INPUT_ELEMENT_DESC> vertexProperties;
	for(int i=0; i<inputElements.size(); i++)
		vertexProperties.push_back(inputElements[i].descriptor);

	HRESULT result = device->CreateInputLayout(&vertexProperties[0], vertexProperties.size(), compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), &inputLayout);
	if(FAILED(result))
		throw DirectXException("Exception while creating input layout!");

	return new InputLayout(inputLayout);
}

SwapChain* Device::createSwapChain(SwapChainDescriptor& descriptor) const
{
	CComQIPtr<IDXGIDevice> dxgiDevice(device);
	
	CComPtr<IDXGIAdapter> dxgiAdapter(nullptr);
	dxgiDevice->GetParent(__uuidof(dxgiAdapter), reinterpret_cast<void**>(&dxgiAdapter));

	CComPtr<IDXGIFactory> dxgiFactory(nullptr);
	dxgiAdapter->GetParent(__uuidof(dxgiFactory), reinterpret_cast<void**>(&dxgiFactory));

	CComPtr<IDXGISwapChain> swapChain(nullptr);
	HRESULT result = dxgiFactory->CreateSwapChain(device, &(descriptor.descriptor), &swapChain);
	if(FAILED(result))
		throw DirectXException("Exception while creating swap chain!");

	return new SwapChain(swapChain, descriptor);
}

SwapChain* Device::createSwapChain(int width, int height, double refreshRate, HWND window) const
{
	SwapChainDescriptor descriptor;
	descriptor.setBufferCount(1);
	descriptor.setBufferSize(width, height);
	descriptor.setBufferFormat(DXGI_FORMAT_R8G8B8A8_UNORM);
	descriptor.setRefreshRate(refreshRate);
	descriptor.setBufferUsage(DXGI_USAGE_RENDER_TARGET_OUTPUT);
	descriptor.setOutputWindow(window);
	descriptor.setWindowed(true);
	descriptor.setMultiSampling(1, 0);

	return createSwapChain(descriptor);
}

PixelShader* Device::createPixelShader(const char* filename, const char* entryPoint, const char* shaderVersion) const
{
	CComPtr<ID3DBlob> compiledShader = nullptr;
	CComPtr<ID3DBlob> errorMessages(nullptr);

	HRESULT result = D3DX11CompileFromFile(filename, nullptr, nullptr, entryPoint, shaderVersion, D3DCOMPILE_ENABLE_STRICTNESS, 0, nullptr, &compiledShader, &errorMessages, nullptr);

	if(errorMessages != nullptr)
		MessageBox(nullptr, static_cast<char*>(errorMessages->GetBufferPointer()), "Shader Compile Errors", MB_OK);

	if(FAILED(result))
		throw DirectXException("Exception while compiling shader!");

	CComPtr<ID3D11PixelShader> pixelShader(nullptr);
	result = device->CreatePixelShader(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), nullptr, &pixelShader);
	if(FAILED(result))
		throw DirectXException("Exception while creating vertex shader!");

	return new PixelShader(pixelShader);
}

RenderTargetView* Device::createRenderTargetView(const Resource* resource) const
{
	if(resource == nullptr)
		return nullptr;

	CComPtr<ID3D11RenderTargetView> view(nullptr);
	HRESULT result = device->CreateRenderTargetView(resource->resource, nullptr, &view);
	if(FAILED(result))
		throw DirectXException("Exception while creating render target!");

	return new RenderTargetView(view);
}

SamplerState* Device::createSamplerState(const SamplerDescriptor& samplerDescriptor) const
{
	CComPtr<ID3D11SamplerState> samplerState(nullptr);

	HRESULT result = device->CreateSamplerState(&(samplerDescriptor.descriptor), &samplerState);
	if(FAILED(result))
		throw DirectXException("Exception while creating sampler state!");

	return new SamplerState(samplerState);
}

ShaderResourceView* Device::createShaderResourceViewFromFile(const char* fileName) const
{
	CComPtr<ID3D11ShaderResourceView> view(nullptr);

	HRESULT result = D3DX11CreateShaderResourceViewFromFile(device, fileName, nullptr, nullptr, &view, nullptr);
	if(FAILED(result))
		throw DirectXException("Exception while creating Shader Resource View!");

	return new ShaderResourceView(view);
}

Buffer* Device::createVertexBuffer(int bufferSize, const void* bufferData) const
{
	D3D11_BUFFER_DESC bufferDescriptor;
	ZeroMemory(&bufferDescriptor, sizeof(bufferDescriptor));

	bufferDescriptor.Usage = D3D11_USAGE_DEFAULT;
	bufferDescriptor.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDescriptor.ByteWidth = bufferSize;

	D3D11_SUBRESOURCE_DATA subResourceData;
	ZeroMemory(&subResourceData, sizeof(subResourceData));
	subResourceData.pSysMem = bufferData;

	CComPtr<ID3D11Buffer> buffer(nullptr);
	HRESULT result = device->CreateBuffer(&bufferDescriptor, &subResourceData, &buffer);
	if(FAILED(result))
		throw DirectXException("Exception while creating vertex buffer!");

	return new Buffer(buffer);
}

VertexShader* Device::createVertexShader(const char* filename, const char* entryPoint, const char* shaderVersion) const
{
	CComPtr<ID3DBlob> compiledShader(nullptr);
	CComPtr<ID3DBlob> errorMessages(nullptr);

	HRESULT result = D3DX11CompileFromFile(filename, nullptr, nullptr, entryPoint, shaderVersion, D3DCOMPILE_ENABLE_STRICTNESS, 0, nullptr, &compiledShader, &errorMessages, nullptr);

	if(errorMessages != nullptr)
		MessageBox(nullptr, static_cast<char*>(errorMessages->GetBufferPointer()), "Shader Compile Errors", MB_OK);

	if(FAILED(result))
		throw DirectXException("Exception while compiling shader!");

	CComPtr<ID3D11VertexShader> vertexShader(nullptr);
	result = device->CreateVertexShader(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), nullptr, &vertexShader);
	if(FAILED(result))
		throw DirectXException("Exception while creating vertex shader!");

	return new VertexShader(vertexShader, compiledShader);
}