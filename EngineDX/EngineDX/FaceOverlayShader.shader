// this shader model contains two constant buffers
// 1 -> TickConstantBuffer, used to pass data which updates every frame
// 2 -> OnEvent, is only triggered on certian events. it is rarely called
// 	 	-- used for things such as projection matrix whis is updated on WM_SIZE

cbuffer TickConstantBuffer : register(b0)
{
	matrix World;
	matrix View;
	float4 vLightDirection;
	float4 vLightColor;
}

cbuffer OnEvent : register(b1)
{
	matrix Projection;
	float3 vAmbientDown;
	float3 vAmbientRange;
}

struct VSInput
{
	float4 Pos	: POSITION;
	float3 Norm : NORMAL;
	float2 UV : TEXCOORD;
};

struct PSInput
{
	float4 Pos	: SV_POSITION;
	float3 Norm : TEXCOORD0;
	float4 HemiAmbient : TEXCOORD1;
};

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// COMPUTE HEMISPHERIC LIGHTING HELPER FUNCTION ------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
float4 ComputeAmbient(float3 normal, float3 color)
{
	float up = normal.y * 0.5 + 0.5;
	float3 Ambient = vAmbientDown + up * (vAmbientDown);
	return float4(Ambient * color, 1.f);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// VERTEX SHADER -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
PSInput VShader( VSInput input )
{
	// calculating the hemispheric ambient lighting
	float3 normal = normalize(input.Norm);
	float4 color = float4(0.5f, 0.5f, 0.52f, 1.f);
	color = float4(color.rgb * color.rgb, color.a);
	//----------------------------------------------

	PSInput output = (PSInput)0;
		output.Pos 			= mul(input.Pos, World);
		output.Pos 			= mul(output.Pos, View);
		output.Pos 			= mul(output.Pos, Projection);
		output.HemiAmbient 	= ComputeAmbient(input.Norm, color.xyz);
		output.Norm 		= mul(float4(input.Norm, 1), World).xyz;

	return output;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// GEOMETRY SHADER -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
[maxvertexcount(3)]
void GShader( triangle PSInput input[3], inout TriangleStream<PSInput> OutputStream )
{
	for (int i = 0; i < 3; i++)
    	OutputStream.Append(input[i]);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// PIXEL SHADER ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
float4 PShader( PSInput input ) : SV_TARGET
{
	return float4(0.6f, 0.f, 0.f, 1.f);
}