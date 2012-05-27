#ifndef DIRECTX_SAMPLER_STATE
#define DIRECTX_SAMPLER_STATE

#include <D3D11.h>
#include <atlbase.h>

class SamplerState
{
	friend class Device;
	friend class DeviceContext;

	private:
		CComPtr<ID3D11SamplerState> state;

		SamplerState(const CComPtr<ID3D11SamplerState>& samplerState);
};

#endif