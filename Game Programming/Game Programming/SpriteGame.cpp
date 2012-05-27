#include "Includes\SpriteGame.h"

SpriteGame::SpriteGame() : vertexBuffer(nullptr), inputLayout(nullptr), vertexShader(nullptr), pixelShader(nullptr), texture(nullptr), textureSampler(nullptr), blendState(nullptr), mvpMatrixBuffer(nullptr)
{
	vpMatrix = XMMatrixIdentity();
}

SpriteGame::~SpriteGame()
{
}

CComPtr<ID3DBlob> SpriteGame::compileShader(const char* filename, const char* entryPoint, const char* shaderVersion)
{
	CComPtr<ID3DBlob> compiledShader(nullptr);
	CComPtr<ID3DBlob> compileErrors(nullptr);

	HRESULT result = D3DX11CompileFromFile(filename, nullptr, nullptr, entryPoint, shaderVersion, 0, 0, nullptr, &compiledShader, &compileErrors, nullptr);
	
	if(compileErrors != nullptr)
		MessageBox(nullptr, static_cast<char*>(compileErrors->GetBufferPointer()), "Shader Compile Error", MB_OK);
	
	if(FAILED(result))
		return nullptr;

	return compiledShader;
}

bool SpriteGame::loadContent()
{
	CComPtr<ID3DBlob> compiledShader(compileShader("SpriteShader.fx", "VS_Main", "vs_4_0"));
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

	compiledShader = compileShader("SpriteShader.fx", "PS_Main", "ps_4_0");
	if(compiledShader == nullptr)
		return false;

	result = device->CreatePixelShader(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), nullptr, &pixelShader);
	if(FAILED(result))
		return false;

	result = D3DX11CreateShaderResourceViewFromFile(device, "Resources/Sprite.dds", nullptr, nullptr, &texture, nullptr);
	if(FAILED(result))
		return false;

	D3D11_SAMPLER_DESC samplerDescriptor;
	ZeroMemory(&samplerDescriptor, sizeof(samplerDescriptor));
	samplerDescriptor.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDescriptor.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDescriptor.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDescriptor.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDescriptor.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDescriptor.MaxLOD = D3D11_FLOAT32_MAX;
	result = device->CreateSamplerState(&samplerDescriptor, &textureSampler);
	if(FAILED(result))
		return false;

	CComPtr<ID3D11Resource> textureResource;
	texture->GetResource(&textureResource);
	D3D11_TEXTURE2D_DESC textureDescriptor;
	((ID3D11Texture2D*)(textureResource.p))->GetDesc(&textureDescriptor);

	float halfWidth = textureDescriptor.Width/2.0f;
	float halfHeight = textureDescriptor.Height/2.0f;

	Vertex vertices[] = {
							{ XMFLOAT3(-halfWidth,  halfHeight, 1.0f), XMFLOAT2(0.0f, 0.0f) },
							{ XMFLOAT3( halfWidth,  halfHeight, 1.0f), XMFLOAT2(1.0f, 0.0f) },
							{ XMFLOAT3(-halfWidth, -halfHeight, 1.0f), XMFLOAT2(0.0f, 1.0f) },
							{ XMFLOAT3( halfWidth, -halfHeight, 1.0f), XMFLOAT2(1.0f, 1.0f) }
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

	D3D11_BUFFER_DESC matrixBufferDescriptor = {0};
	matrixBufferDescriptor.Usage = D3D11_USAGE_DEFAULT;
	matrixBufferDescriptor.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDescriptor.ByteWidth = sizeof(XMMATRIX);

	result = device->CreateBuffer(&matrixBufferDescriptor, nullptr, &mvpMatrixBuffer);
	if(FAILED(result))
		return false;
	
	sprites[0].setPosition(100, 300);
	sprites[1].setPosition(400, 100);
	
	vpMatrix = XMMatrixIdentity() * XMMatrixOrthographicOffCenterLH(0.0f, 600.0f, 0.0f, 600.0f, 0.1f, 100.0f);

	D3D11_BLEND_DESC blendDescriptor = {0};
	blendDescriptor.RenderTarget[0].BlendEnable = true;
	blendDescriptor.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDescriptor.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDescriptor.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDescriptor.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDescriptor.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	blendDescriptor.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDescriptor.RenderTarget[0].RenderTargetWriteMask = 0x0F;

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	device->CreateBlendState(&blendDescriptor, &blendState);
	deviceContext->OMSetBlendState(blendState, blendFactor, 0xFFFFFFFF);

	return true;
}

void SpriteGame::unloadContent()
{
	blendState.Release();
	mvpMatrixBuffer.Release();

	textureSampler.Release();
	texture.Release();

	pixelShader.Release();
	vertexShader.Release();
	inputLayout.Release();
	vertexBuffer.Release();
}

void SpriteGame::update(float deltaTime)
{
}

void SpriteGame::render()
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

	for(int i=0; i<sizeof(sprites)/sizeof(Sprite); i++)
	{
		XMMATRIX mvpMatrix = sprites[i].getWorldMatrix() * vpMatrix;
		mvpMatrix = XMMatrixTranspose(mvpMatrix);
		
		deviceContext->UpdateSubresource(mvpMatrixBuffer, 0, nullptr, &mvpMatrix, 0, 0);
		deviceContext->VSSetConstantBuffers(0, 1, &(mvpMatrixBuffer.p));
		
		deviceContext->Draw(4, 0);
	}

	swapChain->Present(0, 0);
}