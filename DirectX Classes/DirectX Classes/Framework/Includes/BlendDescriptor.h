#ifndef DIRECTX_BLEND_DESCRIPTOR
#define DIRECTX_BLEND_DESCRIPTOR

#include <D3D11.h>

class BlendDescriptor
{
	friend class Device;

	private:
		D3D11_BLEND_DESC descriptor;
	public:
		BlendDescriptor();

		void enableBlend(int renderTargetIndex);
		void setColorBlend(int renderTargetIndex, D3D11_BLEND_OP blendOperation, D3D11_BLEND sourceBlend, D3D11_BLEND destinationBlend);
		void setAlphaBlend(int renderTargetIndex, D3D11_BLEND_OP blendOperation, D3D11_BLEND sourceBlend, D3D11_BLEND destinationBlend);
};

#endif