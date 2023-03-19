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
	
};

float4 Main(VTX_OUT _in) : SV_Target
{
    float4 color = (float) 0.0f;
        
    if (animationType == 1) // 2D
    {
        
        float2 UV = (leftTop - offset) + spriteSize*_in.vUV;
        
        color = defaultTexture.Sample(PointSampler, UV);
    }
    else
    {
        color = defaultTexture.Sample(AnisotropicSampler, _in.vUV);
    }
    
    
    return color;
}