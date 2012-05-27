#include "Includes\TextureGame.h"


TextureGame::TextureGame() : vertexBuffer(nullptr), inputLayout(nullptr), vertexShader(nullptr), pixelShader(nullptr), texture(nullptr), textureSampler(nullptr)
{
}


TextureGame::~TextureGame()
{
}

CComPtr<ID3DBlob> TextureGame::compileShader(const char* filename, const char* entryPoint, const char* shaderVersion)
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

bool TextureGame::loadContent()
{
	CComPtr<ID3DBlob> compiledShader(compileShader("TextureShader.fx", "VS_Main", "vs_4_0"));
	if(compiledShader == nullptr)
		return false;

	HRESULT result = device->CreateVertexShader(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), nullptr, &vertexShader);
	if(FAILED(result))
		return false;
	
	D3D11_INPUT_ELEMENT_DESC vertexProperties[] =	{
														{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
														{ "TEXEL", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
													};
	result = device->CreateInputLayout(vertexProperties, 2, compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), &inputLayout);

	if(FAILED(result))
		return false;

	compiledShader = compileShader("TextureShader.fx", "PS_Main", "ps_4_0");
	if(compiledShader == nullptr)
		return false;

	result = device->CreatePixelShader(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), nullptr, &pixelShader);
	if(FAILED(result))
		return false;

	Vertex vertices[] = {
							{ XMFLOAT3(-1.0f,  1.0f, 0.5f), XMFLOAT2(0.0f, 0.0f) },
							{ XMFLOAT3( 1.0f,  1.0f, 0.5f), XMFLOAT2(1.0f, 0.0f) },
							{ XMFLOAT3(-1.0f, -1.0f, 0.5f), XMFLOAT2(0.0f, 1.0f) },
							{ XMFLOAT3( 1.0f, -1.0f, 0.5f), XMFLOAT2(1.0f, 1.0f) }
						};

	Vertex verticesForMirror[] = {
									{ XMFLOAT3(-1.0f,  1.0f, 0.5f), XMFLOAT2(0.0f, 0.0f) },
									{ XMFLOAT3( 1.0f,  1.0f, 0.5f), XMFLOAT2(2.0f, 0.0f) },
									{ XMFLOAT3(-1.0f, -1.0f, 0.5f), XMFLOAT2(0.0f, 2.0f) },
									{ XMFLOAT3( 1.0f, -1.0f, 0.5f), XMFLOAT2(2.0f, 2.0f) }
								 };
	D3D11_BUFFER_DESC bufferDescriptor = {0};
	bufferDescriptor.Usage = D3D11_USAGE_DEFAULT;
	bufferDescriptor.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDescriptor.ByteWidth = sizeof(vertices);

	D3D11_SUBRESOURCE_DATA vertexData = {0};
	vertexData.pSysMem = vertices;

	result = device->CreateBuffer(&bufferDescriptor, &vertexData, &vertexBuffer);
	if(FAILED(result))
		return false;

	result = D3DX11CreateShaderResourceViewFromFile(device, "Resources/Texture.dds", nullptr, nullptr, &texture, nullptr);
	if(FAILED(result))
		return false;

	D3D11_SAMPLER_DESC samplerDescriptor;
	ZeroMemory(&samplerDescriptor, sizeof(samplerDescriptor));
	samplerDescriptor.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;//D3D11_TEXTURE_ADDRESS_MIRROR;
	samplerDescriptor.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDescriptor.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDescriptor.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDescriptor.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDescriptor.MaxLOD = D3D11_FLOAT32_MAX;
	result = device->CreateSamplerState(&samplerDescriptor, &textureSampler);
	if(FAILED(result))
		return false;

	return true;
}

void TextureGame::unloadContent()
{
	textureSampler.Release();
	texture.Release();

	pixelShader.Release();
	vertexShader.Release();
	inputLayout.Release();
	vertexBuffer.Release();
}

void TextureGame::update(float deltaTime)
{
}

void TextureGame::render()
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

	deviceContext->PSSetShaderResources(0, 1, &(texture.p));
	deviceContext->PSSetSamplers(0, 1, &(textureSampler.p));

	deviceContext->Draw(4, 0);

	swapChain->Present(0, 0);
}