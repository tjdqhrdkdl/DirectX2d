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
        
    color = float4(_in.vPos.y / 1000, _in.vPos.y / 1000, 1.0f, 1.0f);
    
    LightColor lightColor = (LightColor) 0.0f;
    for (int i = 0; i < numberOfLight; i++)
    {
        CalculateLightNoZ(lightColor, _in.vWorldPos.xyz,false, i);
    }
    
    color *= lightColor.diffuse;
    return color;
}