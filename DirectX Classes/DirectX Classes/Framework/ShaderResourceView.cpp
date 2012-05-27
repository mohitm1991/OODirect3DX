#include "Includes\ShaderResourceView.h"
#include "Includes\DirectXException.h"
#include "Includes\Resource.h"

ShaderResourceView::ShaderResourceView(const CComPtr<ID3D11ShaderResourceView>& srv) : view(srv)
{
}

Resource* ShaderResourceView::getResource()
{
	if(view == nullptr)
		throw DirectXException("Exception while getting resource from SRV!");

	CComPtr<ID3D11Resource> resource;
	view->GetResource(&resource);
	return new Resource(resource);
}