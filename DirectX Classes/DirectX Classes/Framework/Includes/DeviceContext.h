#ifndef DIRECTX_DEVICE_CONTEXT
#define DIRECTX_DEVICE_CONTEXT

#include<D3D11.h>
#include <atlbase.h>
#include <vector>
using std::vector;

class BlendState;
class Buffer;
class InputLayout;
class PixelShader;
class RenderTargetView;
class ShaderResourceView;
class SamplerState;
class VertexShader;
class ViewPort;

class DeviceContext
{
	friend class Device;

	private:
		CComPtr<ID3D11DeviceContext> deviceContext;
	public:
		DeviceContext();
		void clearRenderTargetView(const RenderTargetView* renderTargetView, float color[4]);
		void draw(int vertexCount, int offset);
		void setBlendState(const BlendState* blendState, float blendFactor[]);
		void setInputLayout(const InputLayout* inputLayout);
		void setPixelShader(const PixelShader* pixelShader);
		void setPixelShaderResource(int slot, const ShaderResourceView* shaderResourceView);
		void setPixelShaderResources(int firstSlot, const vector<const ShaderResourceView*>& shaderResourceViews);
		void setPixelShaderSampler(int slot, const SamplerState* samplerState);
		void setPixelShaderSamplers(int firstSlot, const vector<const SamplerState*>& samplerStates);
		void setRenderTarget(const RenderTargetView* renderTargerView);
		void setRenderTargets(const vector<const RenderTargetView*>& renderTargetViews);
		void setTopology(D3D_PRIMITIVE_TOPOLOGY topology);
		void setVertexBuffer(int slot, const Buffer* vertexBuffer, unsigned int stride, unsigned int offset);
		void setVertexBuffers(int firstSlot, const vector<const Buffer*>& vertexBuffers, vector<unsigned int>& strides, vector<unsigned int>& offsets);
		void setVertexShader(const VertexShader* vertexShader);
		void setVertexShaderBuffer(int slot, const Buffer* constantBuffer);
		void setVertexShaderBuffers(int firstSlot, const vector<const Buffer*>& constantBuffers);
		void setViewPort(const ViewPort& viewPort);
		void setViewPorts(const vector<ViewPort>& viewPorts);
		void updateBuffer(Buffer* constantBuffer, const void* data);
};

#endif