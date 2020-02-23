TextureCube txDiffuse : register( t0 );
SamplerState samLinear : register( s0 );

struct VS_INPUT
{
    float4 Pos : POSITION;
    float3 Norm : NORMAL;
    float3 uvw : TEXCOORD;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 uvw : TEXCOORD0;
};

cbuffer TickConstantBuffer : register(b0)
{
	matrix View;
}

cbuffer OnEvent : register(b1)
{
	matrix Projection;
}

PS_INPUT SKYMAP_VS( VS_INPUT input )
{
    PS_INPUT Out;

    Out.Pos = mul(input.Pos, View);
    Out.Pos = mul(Out.Pos, Projection);
    Out.uvw = input.uvw;
    return Out;
}

[maxvertexcount(3)]
void SKYMAP_GS( triangle PS_INPUT input[3], inout TriangleStream<PS_INPUT> OutputStream )
{
	for (int i = 0; i < 3; i++)
    	OutputStream.Append(input[i]);
}

float4 SKYMAP_PS( PS_INPUT input ) : SV_Target
{
    //return txDiffuse.Sample( samLinear, input.uvw );
    return float4(1.0f, 0.0f, 0.0f, 0.f);
}