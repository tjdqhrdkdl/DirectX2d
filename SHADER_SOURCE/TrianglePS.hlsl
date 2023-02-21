#include "Global.hlsli"


float4 PS_Test(VTX_OUT _in) : SV_Target
{
    float4 color = (float) 0.0f;
    
    color = defaultTexture.Sample(LinearSampler, _in.vUV);
    
	return color;
}