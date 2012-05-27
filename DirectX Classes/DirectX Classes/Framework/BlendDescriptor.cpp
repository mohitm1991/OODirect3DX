#include "Includes\BlendDescriptor.h"

BlendDescriptor::BlendDescriptor() : descriptor()
{
}

void BlendDescriptor::enableBlend(int i)
{
	descriptor.RenderTarget[i].BlendEnable = true;
	descriptor.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
}

void BlendDescriptor::setColorBlend(int i, D3D11_BLEND_OP blendOperation, D3D11_BLEND sourceBlend, D3D11_BLEND destinationBlend)
{
	descriptor.RenderTarget[i].BlendOp = blendOperation;
	descriptor.RenderTarget[i].SrcBlend = sourceBlend;
	descriptor.RenderTarget[i].DestBlend = destinationBlend;
}

void BlendDescriptor::setAlphaBlend(int i, D3D11_BLEND_OP blendOperation, D3D11_BLEND sourceBlend, D3D11_BLEND destinationBlend)
{
	descriptor.RenderTarget[i].BlendOpAlpha = blendOperation;
	descriptor.RenderTarget[i].SrcBlendAlpha = sourceBlend;
	descriptor.RenderTarget[i].DestBlendAlpha = destinationBlend;
}