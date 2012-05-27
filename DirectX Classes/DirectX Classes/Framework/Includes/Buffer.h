#ifndef DIRECTX_BUFFER
#define DIRECTX_BUFFER

#include <D3D11.h>
#include <atlbase.h>

class Buffer
{
	friend class Device;
	friend class DeviceContext;

	private:
		CComPtr<ID3D11Buffer> buffer;
	
		Buffer(const CComPtr<ID3D11Buffer>& buffer);
};

#endif