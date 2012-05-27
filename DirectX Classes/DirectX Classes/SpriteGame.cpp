#include "Includes\SpriteGame.h"
#include <D3DX11.h>

SpriteGame::Vertex::Vertex() : position(), textureCoordinate()
{
}

SpriteGame::Vertex::Vertex(const XMFLOAT3& position, const XMFLOAT2& textureCoordinate) : position(position), textureCoordinate(textureCoordinate)
{
}

void SpriteGame::Vertex::setPosition(const XMFLOAT3& position)
{
	this->position = position;
}

XMFLOAT3 SpriteGame::Vertex::getPosition()
{
	return position;
}

void SpriteGame::Vertex::setCoordinate(const XMFLOAT2& textureCoordinate)
{
	this->textureCoordinate = textureCoordinate;
}

XMFLOAT2 SpriteGame::Vertex::getCoordinate()
{
	return textureCoordinate;
}

SpriteGame::SpriteGame() : vertexBuffer(nullptr), inputLayout(nullptr), vertexShader(nullptr), pixelShader(nullptr)
{
}


SpriteGame::~SpriteGame()
{
}

bool SpriteGame::loadContent()
{
	vertexShader.reset(device->createVertexShader("SpriteShader.fx", "VS_Main", "vs_4_0"));

	vector<InputElementDescriptor> inputElements;
	inputElements.push_back(InputElementDescriptor("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, true, 0));
	inputElements.push_back(InputElementDescriptor("TEXEL", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, true, 0));
	inputLayout.reset(device->createInputLayout(inputElements, vertexShader.get()));

	pixelShader.reset(device->createPixelShader("SpriteShader.fx", "PS_Main", "ps_4_0"));

	srvTexture.reset(device->createShaderResourceViewFromFile("Resources/Sprite.dds"));

	SamplerDescriptor samplerDescriptor;
	samplerDescriptor.setModeX(D3D11_TEXTURE_ADDRESS_WRAP);
	samplerDescriptor.setModeY(D3D11_TEXTURE_ADDRESS_WRAP);
	samplerDescriptor.setModeZ(D3D11_TEXTURE_ADDRESS_WRAP);
	samplerDescriptor.setComparator(D3D11_COMPARISON_NEVER);
	samplerDescriptor.setFilter(D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	samplerDescriptor.setMaxLOD(D3D11_FLOAT32_MAX);
	samplerState.reset(device->createSamplerState(samplerDescriptor));

	unique_ptr<Resource> resource(srvTexture->getResource());
	unique_ptr<Texture2D> texture2D(resource->convertToTexture2D());
	float halfWidth = texture2D->getWidth()/2.0f;
	float halfHeight = texture2D->getHeight()/2.0f;

	vector<Vertex> vertices;
	vertices.push_back(Vertex(XMFLOAT3(-halfWidth,  halfHeight, 1.0f), XMFLOAT2(0.0f, 0.0f)));
	vertices.push_back(Vertex(XMFLOAT3( halfWidth,  halfHeight, 1.0f), XMFLOAT2(1.0f, 0.0f)));
	vertices.push_back(Vertex(XMFLOAT3(-halfWidth, -halfHeight, 1.0f), XMFLOAT2(0.0f, 1.0f)));
	vertices.push_back(Vertex(XMFLOAT3( halfWidth, -halfHeight, 1.0f), XMFLOAT2(1.0f, 1.0f)));
	vertexBuffer.reset(device->createVertexBuffer(vertices.size() * sizeof(Vertex), &vertices[0]));

	matrixBuffer.reset(device->createConstantBuffer(sizeof(viewProjectionMatrix)));

	BlendDescriptor blendDescriptor;
	blendDescriptor.enableBlend(0);
	blendDescriptor.setColorBlend(0, D3D11_BLEND_OP_ADD, D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA);
	blendDescriptor.setAlphaBlend(0, D3D11_BLEND_OP_ADD, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO);
	blendState.reset(device->createBlendState(blendDescriptor));
	float factor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	deviceContext->setBlendState(blendState.get(), factor);

	RECT dimensions;
	GetClientRect(window, &dimensions);
	int width = dimensions.right - dimensions.left;
	int height = dimensions.bottom - dimensions.top;

	viewProjectionMatrix = Matrix::createIdentity() * Matrix::createLeftOrthographicOffCenter(0, width, 0, height, 0.1f, 100.0f);

	sprites[0].setPosition(100, 300);
	sprites[1].setPosition(300, 100);
	sprites[2].setPosition(500, 300);

	angleStep = 0.0f;
	scaleStep = angleStep/XM_PI;
	angleFactor = XM_PI/3600.0f;

	return true;
}

void SpriteGame::unloadContent()
{
	matrixBuffer.reset(nullptr);
	vertexBuffer.reset(nullptr);
	samplerState.reset(nullptr);
	srvTexture.reset(nullptr);
	pixelShader.reset(nullptr);
	inputLayout.reset(nullptr);
	vertexShader.reset(nullptr);
}

void SpriteGame::update(float deltaTime)
{
	float scaleVal = 0.5f + scaleStep;
	float posVal = 100.0f + 400*scaleStep;

	sprites[0].setRotationAngle(angleStep);
	sprites[1].setPosition(300, posVal);
	//sprites[1].setRotationAngle(XM_PI - angleStep);
	sprites[1].setScale(scaleVal, scaleVal);
	sprites[2].setRotationAngle(2*XM_PI - angleStep);

	angleStep += angleFactor;
	if(angleStep >= 2*XM_PI)
		angleStep = 0.0f;
	if(angleStep <= XM_PI)
		scaleStep = angleStep/XM_PI;
	else
		scaleStep = 2 - angleStep/XM_PI;
}

void SpriteGame::render()
{
	if(deviceContext == nullptr)
		return;

	float black[4] = { 1.0f, 0.5f, 0.0f, 1.0f };
	deviceContext->clearRenderTargetView(backBuffer.get(), black);

	deviceContext->setInputLayout(inputLayout.get());
	deviceContext->setVertexBuffer(0, vertexBuffer.get(), sizeof(Vertex), 0);
	deviceContext->setTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	deviceContext->setVertexShader(vertexShader.get());
	deviceContext->setPixelShader(pixelShader.get());

	deviceContext->setPixelShaderResource(0, srvTexture.get());
	deviceContext->setPixelShaderSampler(0, samplerState.get());

	for(int i=0; i<sizeof(sprites)/sizeof(Sprite); i++)
	{
		Matrix mvpMatrix = sprites[i].getWorldMatrix() * viewProjectionMatrix;
		mvpMatrix = mvpMatrix.transpose();

		deviceContext->updateBuffer(matrixBuffer.get(), &(mvpMatrix.getNative()));
		deviceContext->setVertexShaderBuffer(0, matrixBuffer.get());

		deviceContext->draw(4, 0);
	}

	swapChain->rotateChain();
}