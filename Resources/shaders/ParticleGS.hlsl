#include "Particle.hlsli"

static const uint vnum = 4;

static const float4 offset_array[vnum] =
{
	float4(-0.5,-0.5f,0,0),
	float4(-0.5,+0.5f,0,0),
	float4(+0.5,-0.5f,0,0),
	float4(+0.5,+0.5f,0,0),
};

static const float2 uv_array[vnum] =
{
	float2(0,1),
	float2(0,0),
	float2(1,1),
	float2(1,0)
};

[maxvertexcount(vnum)]
void main(
	point VSOutput input[1] : SV_POSITION, 
	inout TriangleStream< GSOutput > output
)
{

	GSOutput element;

	for (uint i = 0; i < vnum; i++)
	{
		float4 offset = offset_array[i]*input[0].scale;

		float sinX = sin(input[0].rotate);
		float cosX = cos(input[0].rotate);

		float2x2 rot= float2x2(cosX, -sinX, sinX, cosX);

		offset.xy = mul(rot, offset.xy);

		offset = mul(matBillboard, offset);

		element.svpos = input[0].pos+ offset;
		element.svpos = mul(mat,element.svpos);
		element.uv = uv_array[i];
		element.color = input[0].color;
		output.Append(element);

	}

	

}