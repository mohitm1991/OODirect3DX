#include "Includes\DeviceContext.h"
#include "Includes\BlendState.h"
#include "Includes\Buffer.h"
#include "Includes\InputLayout.h"
#include "Includes\PixelShader.h"
#include "Includes\RenderTargetView.h"
#include "Includes\ShaderResourceView.h"
#include "Includes\SamplerState.h"
#include "Includes\VertexShader.h"
#include "Includes\ViewPort.h"

DeviceContext::DeviceContext() : deviceContext(nullptr)
{
}

void DeviceContext::clearRenderTargetView(const RenderTargetView* renderTargetView, float color[4])
{
	deviceContext->ClearRenderTargetView(renderTargetView->view, color);
}

void DeviceContext::draw(int vertexCount, int offset)
{
	deviceContext->Draw(vertexCount, offset);
}

void DeviceContext::setBlendState(const BlendState* blendState, float blendFactor[])
{
	deviceContext->OMSetBlendState(blendState->state, blendFactor, 0xFFFFFFFF);
}

void DeviceContext::setInputLayout(const InputLayout* inputLayout)
{
	deviceContext->IASetInputLayout(inputLayout->layout);
}

void DeviceContext::setPixelShader(const PixelShader* pixelShader)
{
	deviceContext->PSSetShader(pixelShader->shader, nullptr, 0);
}

void DeviceContext::setPixelShaderResource(int slot, const ShaderResourceView* shaderResourceView)
{
	deviceContext->PSSetShaderResources(slot, 1, &(shaderResourceView->view.p));
}

void DeviceContext::setPixelShaderResources(int firstSlot, const vector<const ShaderResourceView*>& shaderResourceViews)
{
	int count = shaderResourceViews.size();

	if(count == 1)
	{
		setPixelShaderResource(firstSlot, shaderResourceViews[0]);
		return;
	}

	vector<ID3D11ShaderResourceView*> nativeViews;
	for(int i=0; i<count; i++)
		nativeViews.push_back(shaderResourceViews[i]->view.p);

	deviceContext->PSSetShaderResources(firstSlot, count, &nativeViews[0]);
}

void DeviceContext::setPixelShaderSampler(int slot, const SamplerState* samplerState)
{
	deviceContext->PSSetSamplers(slot, 1, &(samplerState->state.p));
}

void DeviceContext::setPixelShaderSamplers(int firstSlot, const vector<const SamplerState*>& samplerStates)
{
	int count = samplerStates.size();

	if(count == 1)
	{
		setPixelShaderSampler(firstSlot, samplerStates[0]);
		return;
	}

	vector<ID3D11SamplerState*> nativeSamplers;
	for(int i=0; i<count; i++)
		nativeSamplers.push_back(samplerStates[i]->state);

	deviceContext->PSSetSamplers(firstSlot, count, &nativeSamplers[0]);
}

void DeviceContext::setRenderTarget(const RenderTargetView* renderTargetView)
{
	deviceContext->OMSetRenderTargets(1, &(renderTargetView->view.p), nullptr);
}

void DeviceContext::setRenderTargets(const vector<const RenderTargetView*>& renderTargetViews)
{
	int count = renderTargetViews.size();

	if(count == 1)
	{
		setRenderTarget(renderTargetViews[0]);
		return;
	}

	vector<ID3D11RenderTargetView*> nativeViews;
	for(int i=0; i<count; i++)
		nativeViews.push_back(renderTargetViews[i]->view.p);

	deviceContext->OMSetRenderTargets(count, &nativeViews[0], nullptr);
}

void DeviceContext::setTopology(D3D_PRIMITIVE_TOPOLOGY topology)
{
	deviceContext->IASetPrimitiveTopology(topology);
}

void DeviceContext::setVertexBuffer(int slot, const Buffer* vertexBuffer, unsigned int stride, unsigned int offset)
{
	deviceContext->IASetVertexBuffers(slot, 1, &(vertexBuffer->buffer.p), &stride, &offset);
}

void DeviceContext::setVertexBuffers(int firstSlot, const vector<const Buffer*>& vertexBuffers, vector<unsigned int>& strides, vector<unsigned int>& offsets)
{
	int count = vertexBuffers.size();

	if(count == 1)
	{
		setVertexBuffer(firstSlot, vertexBuffers[0], strides[0], offsets[0]);
		return;
	}

	vector<ID3D11Buffer*> nativeBuffers;
	for(int i=0; i<count; i++)
		nativeBuffers.push_back(vertexBuffers[i]->buffer.p);

	deviceContext->IASetVertexBuffers(firstSlot, count, &nativeBuffers[0], &strides[0], &offsets[0]);
}

void DeviceContext::setVertexShader(const VertexShader* vertexShader)
{
	deviceContext->VSSetShader(vertexShader->shader.p, nullptr, 0);
}

void DeviceContext::setVertexShaderBuffer(int slot, const Buffer* constantBuffer)
{
	deviceContext->VSSetConstantBuffers(slot, 1, &(constantBuffer->buffer.p));
}

void DeviceContext::setVertexShaderBuffers(int firstSlot, const vector<const Buffer*>& constantBuffers)
{
	int count = constantBuffers.size();

	if(count == 1)
	{
		setVertexShaderBuffer(firstSlot, constantBuffers[0]);
		return;
	}

	vector<ID3D11Buffer*> nativeBuffers;
	for(int i=0; i<count; i++)
		nativeBuffers.push_back(constantBuffers[i]->buffer.p);

	deviceContext->VSSetConstantBuffers(firstSlot, count, &nativeBuffers[0]);
}

void DeviceContext::setViewPort(const ViewPort& viewPort)
{
	deviceContext->RSSetViewports(1, &(viewPort.viewPort));
}

void DeviceContext::setViewPorts(const vector<ViewPort>& viewPorts)
{
	int count = viewPorts.size();

	if(count == 1)
	{
		setViewPort(viewPorts[0]);
		return;
	}

	vector<D3D11_VIEWPORT> nativePorts;
	for(int i=0; i<count; i++)
		nativePorts.push_back(viewPorts[i].viewPort);

	deviceContext->RSSetViewports(count, &nativePorts[0]);
}

void DeviceContext::updateBuffer(Buffer* constantBuffer, const void* data)
{
	deviceContext->UpdateSubresource(constantBuffer->buffer, 0, nullptr, data, 0, 0);
}