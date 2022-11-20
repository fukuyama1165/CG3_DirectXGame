#include "Particle.hlsli"

VSOutput main(float4 pos : POSITION,float scale: TEXCOORD,float rotate:ROTATE,float4 color:COLOR)
{
	VSOutput output; // ピクセルシェーダーに渡す値
	output.pos =  pos;
	output.scale =  scale;
	output.rotate =  rotate;
	output.color =  color;
	return output;
}