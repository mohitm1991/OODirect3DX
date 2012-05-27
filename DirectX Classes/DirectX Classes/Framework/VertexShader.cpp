#include "Includes\VertexShader.h"
#include "Includes\DirectXException.h"

VertexShader::VertexShader(const CComPtr<ID3D11VertexShader>& vs, const CComPtr<ID3DBlob>& csd) : shader(vs), compiledShaderData(csd)
{
}