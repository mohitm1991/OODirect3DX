#ifndef DIRECTX_SAMPLER_DESCRIPTOR
#define DIRECTX_SAMPLER_DESCRIPTOR

#include <D3D11.h>

class SamplerDescriptor
{
	friend class Device;

	private:
		D3D11_SAMPLER_DESC descriptor;
	public:
		SamplerDescriptor();

		void setModeX(D3D11_TEXTURE_ADDRESS_MODE mode);
		D3D11_TEXTURE_ADDRESS_MODE getModeX();

		void setModeY(D3D11_TEXTURE_ADDRESS_MODE mode);
		D3D11_TEXTURE_ADDRESS_MODE getModeY();

		void setModeZ(D3D11_TEXTURE_ADDRESS_MODE mode);
		D3D11_TEXTURE_ADDRESS_MODE getModeZ();

		void setComparator(D3D11_COMPARISON_FUNC comparatorFunction);
		D3D11_COMPARISON_FUNC getComparator();

		void setFilter(D3D11_FILTER filter);
		D3D11_FILTER getFilter();

		void setMaxLOD(float maxLOD);
		float getMaxLOD();
};

#endif