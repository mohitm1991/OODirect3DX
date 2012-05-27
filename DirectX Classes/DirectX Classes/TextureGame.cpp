#include "Includes\TextureGame.h"

TextureGame::Vertex::Vertex() : position(), textureCoordinate()
{
}

TextureGame::Vertex::Vertex(const XMFLOAT3& position, const XMFLOAT2& textureCoordinate) : position(position), textureCoordinate(textureCoordinate)
{
}

void TextureGame::Vertex::setPosition(const XMFLOAT3& position)
{
	this->position = position;
}

XMFLOAT3 TextureGame::Vertex::getPosition()
{
	return position;
}

void TextureGame::Vertex::setCoordinate(const XMFLOAT2& textureCoordinate)
{
	this->textureCoordinate = textureCoordinate;
}

XMFLOAT2 TextureGame::Vertex::getCoordinate()
{
	return textureCoordinate;
}

TextureGame::TextureGame() : vertexBuffer(nullptr), inputLayout(nullptr), vertexShader(nullptr), pixelShader(nullptr)
{
}

TextureGame::~TextureGame()
{
}

bool TextureGame::loadContent()
{
	vertexShader.reset(device->createVertexShader("TextureShader.fx", "VS_Main", "vs_4_0"));

	vector<InputElementDescriptor> inputElements;
	inputElements.push_back(InputElementDescriptor("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, true, 0));
	inputElements.push_back(InputElementDescriptor("TEXEL", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, true, 0));
	inputLayout.reset(device->createInputLayout(inputElements, vertexShader.get()));

	pixelShader.reset(device->createPixelShader("TextureShader.fx", "PS_Main", "ps_4_0"));

	vector<Vertex> vertices;
	vertices.push_back(Vertex(XMFLOAT3(-1.0f,  1.0f, 0.5f), XMFLOAT2(0.0f, 0.0f)));
	vertices.push_back(Vertex(XMFLOAT3( 1.0f,  1.0f, 0.5f), XMFLOAT2(1.0f, 0.0f)));
	vertices.push_back(Vertex(XMFLOAT3(-1.0f, -1.0f, 0.5f), XMFLOAT2(0.0f, 1.0f)));
	vertices.push_back(Vertex(XMFLOAT3( 1.0f, -1.0f, 0.5f), XMFLOAT2(1.0f, 1.0f)));
	vertexBuffer.reset(device->createVertexBuffer(vertices.size() * sizeof(Vertex), &vertices[0]));

	srvTexture.reset(device->createShaderResourceViewFromFile("Resources/Texture.dds"));

	SamplerDescriptor samplerDescriptor;
	samplerDescriptor.setModeX(D3D11_TEXTURE_ADDRESS_WRAP);
	samplerDescriptor.setModeY(D3D11_TEXTURE_ADDRESS_WRAP);
	samplerDescriptor.setModeZ(D3D11_TEXTURE_ADDRESS_WRAP);
	samplerDescriptor.setComparator(D3D11_COMPARISON_NEVER);
	samplerDescriptor.setFilter(D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	samplerDescriptor.setMaxLOD(D3D11_FLOAT32_MAX);
	samplerState.reset(device->createSamplerState(samplerDescriptor));

	return true;
}

void TextureGame::unloadContent()
{
	samplerState.reset(nullptr);
	srvTexture.reset(nullptr);
	vertexBuffer.reset(nullptr);
	pixelShader.reset(nullptr);
	inputLayout.reset(nullptr);
	vertexShader.reset(nullptr);
}

void TextureGame::update(float deltaTime)
{
}

void TextureGame::render()
{
	if(deviceContext == nullptr)
		return;

	float black[4] = { 0.0f, 0.0f, 0.f, 1.f };
	deviceContext->clearRenderTargetView(backBuffer.get(), black);

	deviceContext->setInputLayout(inputLayout.get());
	deviceContext->setVertexBuffer(0, vertexBuffer.get(), sizeof(Vertex), 0);
	deviceContext->setTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	deviceContext->setVertexShader(vertexShader.get());
	deviceContext->setPixelShader(pixelShader.get());

	deviceContext->setPixelShaderResource(0, srvTexture.get());
	deviceContext->setPixelShaderSampler(0, samplerState.get());

	deviceContext->draw(4, 0);

	swapChain->rotateChain();
}