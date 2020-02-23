struct VS_INPUT
{
    float4 Pos : POSITION;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
};

cbuffer TickConstantBuffer : register(b0)
{
    matrix World;
	matrix View;
}

cbuffer OnEvent : register(b1)
{
	matrix Projection;
}

PS_INPUT WIREFRAME_VS( VS_INPUT input )
{
    PS_INPUT Out;

    Out.Pos = mul(input.Pos, World);
    Out.Pos = mul(Out.Pos, View);
    Out.Pos = mul(Out.Pos, Projection);
    return Out;
}

[maxvertexcount(2)]
void WIREFRAME_GS( line PS_INPUT input[2], inout LineStream<PS_INPUT> OutputStream )
{
    for (int i = 0; i < 2; i++)    
    OutputStream.Append(input[i]);
}

float4 WIREFRAME_PS( PS_INPUT input ) : SV_Target
{
    return float4(0.5f, 0.5f, 0.5f, 0.1f);
}