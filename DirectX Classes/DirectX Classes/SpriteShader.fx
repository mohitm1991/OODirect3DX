Texture2D texture_ : register(t0);
SamplerState sampler_ : register(s0);

cbuffer matrixBuffer : register(b0)
{
	matrix mvpMatrix;
}

struct PS_Input
{
	float4 position : SV_POSITION;
	float2 texel : TEXEL;
};

PS_Input VS_Main(float4 position : POSITION, float2 texel : TEXEL)
{
	PS_Input pixel = { mul(position, mvpMatrix), texel };
	return pixel;
}

float4 PS_Main(PS_Input pixel) : SV_TARGET
{
	return texture_.Sample(sampler_, pixel.texel);
}