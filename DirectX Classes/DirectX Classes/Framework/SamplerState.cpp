#include "Includes\SamplerState.h"

SamplerState::SamplerState(const CComPtr<ID3D11SamplerState>& ss) : state(ss)
{
}