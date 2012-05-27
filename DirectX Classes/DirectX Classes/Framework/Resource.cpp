#include "Includes\Resource.h"
#include "Includes\Texture2D.h"

Resource::Resource() : resource(nullptr)
{
}

Resource::Resource(const CComPtr<ID3D11Resource>& res) : resource(res)
{
}

Resource::~Resource()
{
}

Texture2D* Resource::convertToTexture2D()
{
	if(resource == nullptr)
		return nullptr;

	return new Texture2D(resource);
}