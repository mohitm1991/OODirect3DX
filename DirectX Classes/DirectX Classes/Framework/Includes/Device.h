#ifndef DIRECTX_DEVICE
#define DIRECTX_DEVICE

#include <D3D11.h>
#include <atlbase.h>
#include <vector>
using std::vector;

class BlendDescriptor;
class BlendState;
class Buffer;
class DeviceContext;
class InputElementDescriptor;
class InputLayout;
class PixelShader;
class RenderTargetView;
class Resource;
class SamplerDescriptor;
class SamplerState;
class ShaderResourceView;
class SwapChain;
class SwapChainDescriptor;
class VertexShader;

class Device
{
	private:
		CComPtr<ID3D11Device> device;
	public:
		Device(DeviceContext* deviceContext);

		BlendState* createBlendState(const BlendDescriptor& blendDescriptor);

		Buffer* createConstantBuffer(int bufferSize);

		InputLayout* createInputLayout(const vector<InputElementDescriptor>& inputElements, const VertexShader* vertexShader) const;

		SwapChain* createSwapChain(SwapChainDescriptor& descriptor) const;

		SwapChain* createSwapChain(int width, int height, double refreshRate, HWND window) const;

		PixelShader* createPixelShader(const char* filename, const char* entryPoint, const char* shaderVersion) const;

		RenderTargetView* createRenderTargetView(const Resource* resource) const;

		SamplerState* createSamplerState(const SamplerDescriptor& samplerDescriptor) const;

		ShaderResourceView* createShaderResourceViewFromFile(const char* fileName) const;

		Buffer* createVertexBuffer(int bufferSize, const void* bufferData) const;

		VertexShader* createVertexShader(const char* filename, const char* entryPoint, const char* shaderVersion) const;
};
#endif