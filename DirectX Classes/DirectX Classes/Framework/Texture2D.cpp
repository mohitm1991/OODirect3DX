#include "Includes\Texture2D.h"

Texture2D::Texture2D(const CComPtr<ID3D11Resource>& resource) : texture2D(nullptr), descriptor()
{
	if(resource == nullptr)
		return;

	resource->QueryInterface(&texture2D);
	texture2D->GetDesc(&descriptor);
}

Texture2D::Texture2D(const CComPtr<ID3D11Texture2D>& tex2D) : texture2D(tex2D), descriptor()
{
	if(tex2D != nullptr)
		tex2D->GetDesc(&descriptor);
}

Texture2D::~Texture2D()
{
}

Texture2D* Texture2D::convertToTexture2D()
{
	return new Texture2D(texture2D);
}

int Texture2D::getWidth()
{
	return descriptor.Width;
}

int Texture2D::getHeight()
{
	return descriptor.Height;
}

int Texture2D::getMipLevels()
{
	return descriptor.MipLevels;
}

int Texture2D::getArraySize()
{
	return descriptor.ArraySize;
}

DXGI_FORMAT Texture2D::getFormat()
{
	return descriptor.Format;
}

int Texture2D::getMultiSamplingCount()
{
	return descriptor.SampleDesc.Count;
}

int Texture2D::getMultiSamplingQuality()
{
	return descriptor.SampleDesc.Quality;
}

D3D11_USAGE Texture2D::getUsage()
{
	return descriptor.Usage;
}

int Texture2D::getBindFlags()
{
	return descriptor.BindFlags;
}

int Texture2D::getCpuAccessFlags()
{
	return descriptor.CPUAccessFlags;
}

int Texture2D::getMiscFlags()
{
	return descriptor.MiscFlags;
}