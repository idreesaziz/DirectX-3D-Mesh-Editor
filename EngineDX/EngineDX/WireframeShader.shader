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
    Out.Pos = input.Pos;
    return Out;
}

[maxvertexcount(6)]
void WIREFRAME_GS( line PS_INPUT input[2], inout TriangleStream<PS_INPUT> OutputStream )
{
    float Offset;
    float2 V = mul(mul(input[1].Pos, View), Projection).xy - mul(mul(input[0].Pos, View), Projection).xy;
    float2 vPerpendicular;

    //vPerpendicular.x = V.x * (cos(1.570796326794896f)) + V.y * (sin(1.570796326794896f));
    //vPerpendicular.y = V.x * -1 *(sin(1.570796326794896f)) + V.y * (cos(1.570796326794896f));
    
    vPerpendicular.x = V.y;
    vPerpendicular.y = V.x * -1;

    vPerpendicular /= sqrt(vPerpendicular.x*vPerpendicular.x + vPerpendicular.y*vPerpendicular.y);
    Offset = 0.002 * sqrt(mul(mul(input[0].Pos + input[1].Pos, World), View).z);
    vPerpendicular *= Offset;

    input[0].Pos = mul(input[0].Pos, World);
    input[0].Pos = mul(input[0].Pos, View);

    input[1].Pos = mul(input[1].Pos, World);
    input[1].Pos = mul(input[1].Pos, View);

    PS_INPUT v1;
    v1 = input[0];
    v1.Pos.xy += vPerpendicular;
    v1.Pos = mul(v1.Pos, Projection);

    PS_INPUT v2;
    v2 = input[0];
    v2.Pos.xy -= vPerpendicular;
    v2.Pos = mul(v2.Pos, Projection);

    PS_INPUT v3;
    v3 = input[1];
    v3.Pos.xy += vPerpendicular;
    v3.Pos = mul(v3.Pos, Projection);

    PS_INPUT v4;
    v4 = input[1];
    v4.Pos.xy -= vPerpendicular;
    v4.Pos = mul(v4.Pos, Projection);





    OutputStream.Append(v1);
    OutputStream.Append(v2);
    OutputStream.Append(v3);

    OutputStream.RestartStrip();

    OutputStream.Append(v2);
    OutputStream.Append(v3);
    OutputStream.Append(v4);   
}


float4 WIREFRAME_PS( PS_INPUT input ) : SV_Target
{
    return float4(0.9f, 0.7f, 0.5f, 1.f);
}