cbuffer TickConstantBuffer : register(b0)
{
	matrix World;
	matrix View;
}

cbuffer OnEvent : register(b1)
{
	matrix Projection;
}

struct VS_INPUT
{
    float4 Pos : POSITION;
    float3 Norm : NORMAL;
	float2 UV : TEXCOORD; // i have used the UV channel to check if the vertex is selected
};
struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD0; 
};

PS_INPUT VS( VS_INPUT input )
{
    PS_INPUT output;

    output.Pos = input.Pos;
    output.Pos = input.Pos;
    output.Pos = input.Pos;
    output.UV = input.UV;
    return output;
}

[maxvertexcount(36)]
void GS( point PS_INPUT input[1], inout TriangleStream<PS_INPUT> OutputStream )
{
	float offset = 0.005 * sqrt(mul(input[0].Pos, View).z);
	// making a cube around the vertex
	{
		// first quad
		PS_INPUT v1 = (PS_INPUT)0;
		v1.Pos = float4(input[0].Pos.x - offset, input[0].Pos.y + offset, input[0].Pos.z - offset, input[0].Pos.w);
		v1.UV = input[0].UV;
		PS_INPUT v2 = (PS_INPUT)0;
		v2.Pos = float4(input[0].Pos.x - offset, input[0].Pos.y - offset, input[0].Pos.z - offset, input[0].Pos.w);
		v2.UV = input[0].UV;
		PS_INPUT v3 = (PS_INPUT)0;
		v3.Pos = float4(input[0].Pos.x + offset, input[0].Pos.y + offset, input[0].Pos.z - offset, input[0].Pos.w);
		v3.UV = input[0].UV;
		PS_INPUT v4 = (PS_INPUT)0;
		v4.Pos = float4(input[0].Pos.x + offset, input[0].Pos.y - offset, input[0].Pos.z - offset, input[0].Pos.w);
		v4.UV = input[0].UV;

		v1.Pos = mul(v1.Pos, World); 		v2.Pos = mul(v2.Pos, World); 		v3.Pos = mul(v3.Pos, World);		v4.Pos = mul(v4.Pos, World);
		v1.Pos = mul(v1.Pos, View); 		v2.Pos = mul(v2.Pos, View); 		v3.Pos = mul(v3.Pos, View); 		v4.Pos = mul(v4.Pos, View);
		v1.Pos = mul(v1.Pos, Projection); 	v2.Pos = mul(v2.Pos, Projection); 	v3.Pos = mul(v3.Pos, Projection); 	v4.Pos = mul(v4.Pos, Projection);;

		OutputStream.Append(v1);
		OutputStream.Append(v2);
		OutputStream.Append(v3);
		OutputStream.RestartStrip();
	
		OutputStream.Append(v2);
		OutputStream.Append(v4);
		OutputStream.Append(v3);
		OutputStream.RestartStrip();
	}
	{
		// 2nd quad
		PS_INPUT v1 = (PS_INPUT)0;
		v1.Pos = float4(input[0].Pos.x - offset, input[0].Pos.y + offset, input[0].Pos.z + offset, input[0].Pos.w);
		v1.UV = input[0].UV;
		PS_INPUT v2 = (PS_INPUT)0;
		v2.Pos = float4(input[0].Pos.x - offset, input[0].Pos.y - offset, input[0].Pos.z + offset, input[0].Pos.w);
		v2.UV = input[0].UV;
		PS_INPUT v3 = (PS_INPUT)0;
		v3.Pos = float4(input[0].Pos.x + offset, input[0].Pos.y + offset, input[0].Pos.z + offset, input[0].Pos.w);
		v3.UV = input[0].UV;
		PS_INPUT v4 = (PS_INPUT)0;
		v4.Pos = float4(input[0].Pos.x + offset, input[0].Pos.y - offset, input[0].Pos.z + offset, input[0].Pos.w);
		v4.UV = input[0].UV;

		v1.Pos = mul(v1.Pos, World); 		v2.Pos = mul(v2.Pos, World); 		v3.Pos = mul(v3.Pos, World);		v4.Pos = mul(v4.Pos, World);
		v1.Pos = mul(v1.Pos, View); 		v2.Pos = mul(v2.Pos, View); 		v3.Pos = mul(v3.Pos, View); 		v4.Pos = mul(v4.Pos, View);
		v1.Pos = mul(v1.Pos, Projection); 	v2.Pos = mul(v2.Pos, Projection); 	v3.Pos = mul(v3.Pos, Projection); 	v4.Pos = mul(v4.Pos, Projection);

		OutputStream.Append(v1);
		OutputStream.Append(v2);
		OutputStream.Append(v3);
		OutputStream.RestartStrip();
	
		OutputStream.Append(v2);
		OutputStream.Append(v4);
		OutputStream.Append(v3);
		OutputStream.RestartStrip();

	}
	{
		// 3rd quad
		PS_INPUT v1 = (PS_INPUT)0;
		v1.Pos = float4(input[0].Pos.x - offset, input[0].Pos.y + offset, input[0].Pos.z - offset, input[0].Pos.w);
		v1.UV = input[0].UV;
		PS_INPUT v2 = (PS_INPUT)0;
		v2.Pos = float4(input[0].Pos.x - offset, input[0].Pos.y - offset, input[0].Pos.z - offset, input[0].Pos.w);
		v2.UV = input[0].UV;
		PS_INPUT v3 = (PS_INPUT)0;
		v3.Pos = float4(input[0].Pos.x - offset, input[0].Pos.y + offset, input[0].Pos.z + offset, input[0].Pos.w);
		v3.UV = input[0].UV;
		PS_INPUT v4 = (PS_INPUT)0;
		v4.Pos = float4(input[0].Pos.x - offset, input[0].Pos.y - offset, input[0].Pos.z + offset, input[0].Pos.w);
		v4.UV = input[0].UV;

		v1.Pos = mul(v1.Pos, World); 		v2.Pos = mul(v2.Pos, World); 		v3.Pos = mul(v3.Pos, World);		v4.Pos = mul(v4.Pos, World);
		v1.Pos = mul(v1.Pos, View); 		v2.Pos = mul(v2.Pos, View); 		v3.Pos = mul(v3.Pos, View); 		v4.Pos = mul(v4.Pos, View);
		v1.Pos = mul(v1.Pos, Projection); 	v2.Pos = mul(v2.Pos, Projection); 	v3.Pos = mul(v3.Pos, Projection); 	v4.Pos = mul(v4.Pos, Projection);

		OutputStream.Append(v1);
		OutputStream.Append(v2);
		OutputStream.Append(v3);
		OutputStream.RestartStrip();
		
		OutputStream.Append(v3);
		OutputStream.Append(v4);
		OutputStream.Append(v2);
	}
	{
		// 4th quad
		PS_INPUT v1 = (PS_INPUT)0;
		v1.Pos = float4(input[0].Pos.x + offset, input[0].Pos.y + offset, input[0].Pos.z - offset, input[0].Pos.w);
		v1.UV = input[0].UV;
		PS_INPUT v2 = (PS_INPUT)0;
		v2.Pos = float4(input[0].Pos.x + offset, input[0].Pos.y - offset, input[0].Pos.z - offset, input[0].Pos.w);
		v2.UV = input[0].UV;
		PS_INPUT v3 = (PS_INPUT)0;
		v3.Pos = float4(input[0].Pos.x + offset, input[0].Pos.y + offset, input[0].Pos.z + offset, input[0].Pos.w);
		v3.UV = input[0].UV;
		PS_INPUT v4 = (PS_INPUT)0;
		v4.Pos = float4(input[0].Pos.x + offset, input[0].Pos.y - offset, input[0].Pos.z + offset, input[0].Pos.w);
		v4.UV = input[0].UV;
		
		v1.Pos = mul(v1.Pos, World); 		v2.Pos = mul(v2.Pos, World); 		v3.Pos = mul(v3.Pos, World);		v4.Pos = mul(v4.Pos, World);
		v1.Pos = mul(v1.Pos, View); 		v2.Pos = mul(v2.Pos, View); 		v3.Pos = mul(v3.Pos, View); 		v4.Pos = mul(v4.Pos, View);
		v1.Pos = mul(v1.Pos, Projection); 	v2.Pos = mul(v2.Pos, Projection); 	v3.Pos = mul(v3.Pos, Projection); 	v4.Pos = mul(v4.Pos, Projection);
		
		OutputStream.Append(v1);
		OutputStream.Append(v2);
		OutputStream.Append(v3);
		OutputStream.RestartStrip();
	
		OutputStream.Append(v2);
		OutputStream.Append(v4);
		OutputStream.Append(v3);
		OutputStream.RestartStrip();
	}
	{
		// 5th quad
		PS_INPUT v1 = (PS_INPUT)0;
		v1.Pos = float4(input[0].Pos.x - offset, input[0].Pos.y + offset, input[0].Pos.z - offset, input[0].Pos.w);
		v1.UV = input[0].UV;
		PS_INPUT v2 = (PS_INPUT)0;
		v2.Pos = float4(input[0].Pos.x - offset, input[0].Pos.y + offset, input[0].Pos.z + offset, input[0].Pos.w);
		v2.UV = input[0].UV;
		PS_INPUT v3 = (PS_INPUT)0;
		v3.Pos = float4(input[0].Pos.x + offset, input[0].Pos.y + offset, input[0].Pos.z - offset, input[0].Pos.w);
		v3.UV = input[0].UV;
		PS_INPUT v4 = (PS_INPUT)0;
		v4.Pos = float4(input[0].Pos.x + offset, input[0].Pos.y + offset, input[0].Pos.z + offset, input[0].Pos.w);
		v4.UV = input[0].UV;
		
		v1.Pos = mul(v1.Pos, World); 		v2.Pos = mul(v2.Pos, World); 		v3.Pos = mul(v3.Pos, World);		v4.Pos = mul(v4.Pos, World);
		v1.Pos = mul(v1.Pos, View); 		v2.Pos = mul(v2.Pos, View); 		v3.Pos = mul(v3.Pos, View); 		v4.Pos = mul(v4.Pos, View);
		v1.Pos = mul(v1.Pos, Projection); 	v2.Pos = mul(v2.Pos, Projection); 	v3.Pos = mul(v3.Pos, Projection); 	v4.Pos = mul(v4.Pos, Projection);

		OutputStream.Append(v1);
		OutputStream.Append(v2);
		OutputStream.Append(v3);
		OutputStream.RestartStrip();
	
		OutputStream.Append(v2);
		OutputStream.Append(v4);
		OutputStream.Append(v3);
		OutputStream.RestartStrip();
	}
	{
		// 6th quad
		PS_INPUT v1 = (PS_INPUT)0;
		v1.Pos = float4(input[0].Pos.x - offset, input[0].Pos.y - offset, input[0].Pos.z - offset, input[0].Pos.w);
		v1.UV = input[0].UV;
		PS_INPUT v2 = (PS_INPUT)0;
		v2.Pos = float4(input[0].Pos.x - offset, input[0].Pos.y - offset, input[0].Pos.z + offset, input[0].Pos.w);
		v2.UV = input[0].UV;
		PS_INPUT v3 = (PS_INPUT)0;
		v3.Pos = float4(input[0].Pos.x + offset, input[0].Pos.y - offset, input[0].Pos.z - offset, input[0].Pos.w);
		v3.UV = input[0].UV;
		PS_INPUT v4 = (PS_INPUT)0;
		v4.Pos = float4(input[0].Pos.x + offset, input[0].Pos.y - offset, input[0].Pos.z + offset, input[0].Pos.w);
		v4.UV = input[0].UV;
		
		v1.Pos = mul(v1.Pos, World); 		v2.Pos = mul(v2.Pos, World); 		v3.Pos = mul(v3.Pos, World);		v4.Pos = mul(v4.Pos, World);
		v1.Pos = mul(v1.Pos, View); 		v2.Pos = mul(v2.Pos, View); 		v3.Pos = mul(v3.Pos, View); 		v4.Pos = mul(v4.Pos, View);
		v1.Pos = mul(v1.Pos, Projection); 	v2.Pos = mul(v2.Pos, Projection); 	v3.Pos = mul(v3.Pos, Projection); 	v4.Pos = mul(v4.Pos, Projection);

		OutputStream.Append(v1);
		OutputStream.Append(v2);
		OutputStream.Append(v3);
		OutputStream.RestartStrip();
	
		OutputStream.Append(v2);
		OutputStream.Append(v4);
		OutputStream.Append(v3);
	}
}


float4 PS( PS_INPUT input ) : SV_Target
{
    if (input.UV.x == 1)
            return float4( 1.0f, 0.0f, 0.0f, 1.0f );
	else
    return float4( 0.0f, 0.0f, 1.0f, 1.0f );
}