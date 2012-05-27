struct PS_Input
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

PS_Input VS_Main(float4 position : POSITION, float4 color : COLOR)
{
	PS_Input pixel = { position, color };
	return pixel;
}

float4 PS_Main(PS_Input pixel) : SV_TARGET
{
	return pixel.color;
}