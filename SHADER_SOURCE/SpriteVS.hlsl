#include "Global.hlsli"

VTX_OUT Main(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;

    float4 worldPosition = mul(_in.vPos, worldMatrix);
    float4 viewPosition = mul(worldPosition, viewMatrix);
    float4 projectionPosition = mul(viewPosition, projectionMatrix);


    output.vPos = projectionPosition;
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;

    return output;
}