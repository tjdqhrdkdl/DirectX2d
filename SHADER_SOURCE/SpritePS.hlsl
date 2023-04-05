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

float4 main(VTX_OUT _in) : SV_Target
{
    float4 color = (float) 0.0f;
        
    if (animationType == 1) // 2D
    {
        float2 UV = (leftTop - offset) + spriteSize*_in.vUV;
        if (reversed)
            UV.x = spriteSize.x + 2 * (leftTop.x - offset.x) - UV.x;
        color = defaultTexture.Sample(PointSampler, UV);
    }
    else
    {
        color = defaultTexture.Sample(AnisotropicSampler, _in.vUV);
    }
    
    LightColor lightColor = (LightColor) 0.0f;
    bool transparency = true;
    
    if(color.w == 1.0f)
        transparency = false;
    for (int i = 0; i < numberOfLight; i++)
    {
        CalculateLightNoZ(lightColor, _in.vWorldPos.xyz, transparency,i);
    }
    
    color *= lightColor.diffuse;
    return color;
}