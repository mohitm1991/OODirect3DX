#include "Includes\BlendState.h"

BlendState::BlendState(const CComPtr<ID3D11BlendState>& bs) : state(bs)
{
}