#ifndef DIRECTX_BLEND_STATE
#define DIRECTX_BLEND_STATE

#include <D3D11.h>
#include <atlbase.h>

class BlendState
{
	friend class Device;
	friend class DeviceContext;

	private:
		CComPtr<ID3D11BlendState> state;

		BlendState(const CComPtr<ID3D11BlendState>& blendState);
};

#endif