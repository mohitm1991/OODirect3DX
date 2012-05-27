#include "Includes\SamplerDescriptor.h"

SamplerDescriptor::SamplerDescriptor() : descriptor()
{
}

void SamplerDescriptor::setModeX(D3D11_TEXTURE_ADDRESS_MODE mode)
{
	descriptor.AddressU = mode;
}

D3D11_TEXTURE_ADDRESS_MODE SamplerDescriptor::getModeX()
{
	return descriptor.AddressU;
}

void SamplerDescriptor::setModeY(D3D11_TEXTURE_ADDRESS_MODE mode)
{
	descriptor.AddressV = mode;
}

D3D11_TEXTURE_ADDRESS_MODE SamplerDescriptor::getModeY()
{
	return descriptor.AddressV;
}

void SamplerDescriptor::setModeZ(D3D11_TEXTURE_ADDRESS_MODE mode)
{
	descriptor.AddressW = mode;
}

D3D11_TEXTURE_ADDRESS_MODE SamplerDescriptor::getModeZ()
{
	return descriptor.AddressW;
}

void SamplerDescriptor::setComparator(D3D11_COMPARISON_FUNC comparatorFunction)
{
	descriptor.ComparisonFunc = comparatorFunction;
}

D3D11_COMPARISON_FUNC SamplerDescriptor::getComparator()
{
	return descriptor.ComparisonFunc;
}

void SamplerDescriptor::setFilter(D3D11_FILTER filter)
{
	descriptor.Filter = filter;
}

D3D11_FILTER SamplerDescriptor::getFilter()
{
	return descriptor.Filter;
}

void SamplerDescriptor::setMaxLOD(float maxLOD)
{
	descriptor.MaxLOD = maxLOD;
}

float SamplerDescriptor::getMaxLOD()
{
	return descriptor.MaxLOD;
}