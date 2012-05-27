#include "Includes\PixelShader.h"

PixelShader::PixelShader(const CComPtr<ID3D11PixelShader>& ps) : shader(ps)
{
}