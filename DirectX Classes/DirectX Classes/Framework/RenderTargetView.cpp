#include "Includes\RenderTargetView.h"

RenderTargetView::RenderTargetView(const CComPtr<ID3D11RenderTargetView>& rtv) : view(rtv)
{
}