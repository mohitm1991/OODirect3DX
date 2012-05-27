#include "Includes\TriangleGame.h"

TriangleGame::TriangleGame() : vertexBuffer(nullptr), inputLayout(nullptr), vertexShader(nullptr), pixelShader(nullptr)
{
}


TriangleGame::~TriangleGame()
{
}

CComPtr<ID3DBlob> TriangleGame::compileShader(const char* filename, const char* entryPoint, const char* shaderVersion)
{
	CComPtr<ID3DBlob> compiledShader(nullptr);
	CComPtr<ID3DBlob> compileErrors(nullptr);

	HRESULT result = D3DX11CompileFromFile(filename, nullptr, nullptr, entryPoint, shaderVersion, D3DCOMPILE_ENABLE_STRICTNESS, 0, nullptr, &compiledShader, &compileErrors, nullptr);
	
	if(compileErrors != nullptr)
		MessageBox(nullptr, static_cast<char*>(compileErrors->GetBufferPointer()), "Shader Compile Error", MB_OK);
	
	if(FAILED(result))
		return nullptr;

	return compiledShader;
}

bool TriangleGame::loadContent()
{
	CComPtr<ID3DBlob> compiledShader(compileShader("TriangleShader.fx", "VS_Main", "vs_4_0"));
	if(compiledShader == nullptr)
		return false;

	HRESULT result = device->CreateVertexShader(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), nullptr, &vertexShader);
	if(FAILED(result))
		return false;
	
	D3D11_INPUT_ELEMENT_DESC vertexProperties[] =	{
														{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	 0,	 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
														{ "COLOR",	  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
													};
	result = device->CreateInputLayout(vertexProperties, 2, compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), &inputLayout);

	if(FAILED(result))
		return false;

	compiledShader = compileShader("TriangleShader.fx", "PS_Main", "ps_4_0");
	if(compiledShader == nullptr)
		return false;

	result = device->CreatePixelShader(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), nullptr, &pixelShader);
	if(FAILED(result))
		return false;

	Vertex vertices[] = {
							{ XMFLOAT3(-0.5f,  1.0f, 0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
							{ XMFLOAT3( 0.5f,  1.0f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
							{ XMFLOAT3(-0.5f,  0.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
							{ XMFLOAT3( 0.5f,  0.0f, 0.5f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
							{ XMFLOAT3(-0.5f, -1.0f, 0.5f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
							{ XMFLOAT3( 0.5f, -1.0f, 0.5f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) }
						};
	D3D11_BUFFER_DESC bufferDescriptor;
	ZeroMemory(&bufferDescriptor, sizeof(bufferDescriptor));
	bufferDescriptor.Usage = D3D11_USAGE_DEFAULT;
	bufferDescriptor.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDescriptor.ByteWidth = 6 * sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA vertexData;
	ZeroMemory(&vertexData, sizeof(vertexData));
	vertexData.pSysMem = vertices;

	result = device->CreateBuffer(&bufferDescriptor, &vertexData, &vertexBuffer);
	if(FAILED(result))
		return false;

	return true;
}

void TriangleGame::unloadContent()
{
	pixelShader.Release();
	vertexShader.Release();
	inputLayout.Release();
	vertexBuffer.Release();
}

void TriangleGame::update(float deltaTime)
{
}

void TriangleGame::render()
{
	float backgroundColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	deviceContext->ClearRenderTargetView(backBuffer, backgroundColor);

	unsigned int stride = sizeof(Vertex);
	unsigned int offset = 0;
	deviceContext->IASetInputLayout(inputLayout);
	deviceContext->IASetVertexBuffers(0, 1, &(vertexBuffer.p), &stride, &offset);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	deviceContext->VSSetShader(vertexShader, nullptr, 0);
	deviceContext->PSSetShader(pixelShader, nullptr, 0);

	deviceContext->Draw(6, 0);

	swapChain->Present(0, 0);
}