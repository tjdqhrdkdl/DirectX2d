#include "Global.hlsli"

struct VTX_IN
{
    float4 vPos : POSITION;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
	
};

struct VTX_OUT
{
    float4 vPos : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
	
    float3 vWorldPos : POSITION;
};
VTX_OUT Main(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;

    float4 worldPosition = mul(_in.vPos, worldMatrix);
    float4 viewPosition = mul(worldPosition, viewMatrix);
    float4 projectionPosition = mul(viewPosition, projectionMatrix);


    output.vPos = projectionPosition;
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    output.vWorldPos = worldPosition;

    return output;
}