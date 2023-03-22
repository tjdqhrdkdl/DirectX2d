#include "Light.hlsli"

cbuffer Transform : register(b0)
{
    row_major matrix worldMatrix;
    row_major matrix viewMatrix;
    row_major matrix projectionMatrix;
    
};

cbuffer MaterialData : register(b1)
{
    int cbiData;
    float cbfData;
    float2 cbVector2;
    float3 cbVector3;
    float4 cbVector4;
    matrix cbMatrix;
};

cbuffer AnimatorData : register(b2)
{
    float2 leftTop;
    float2 spriteSize;
    float2 offset;
    bool reversed;

    uint animationType;
};

cbuffer NumberOfLight : register(b3)
{
    uint numberOfLight;
}


Texture2D defaultTexture : register(t0);

StructuredBuffer<LightAttribute> lightAttributes : register(t12);
//
SamplerState PointSampler : register(s0);
SamplerState LinearSampler : register(s1);
SamplerState AnisotropicSampler : register(s2);

//
void CalculateLight(in out LightColor pLightColor, float3 position, int idx)
{
    if (0 == lightAttributes[idx].type)
    {
        pLightColor.diffuse += lightAttributes[idx].color.diffuse;
    }
    else if (1 == lightAttributes[idx].type)
    {
        float length = distance(lightAttributes[idx].position.xy, position.xy);
        
        if (length < lightAttributes[idx].radius)
        {
            float ratio = 1.0f - (length / lightAttributes[idx].radius);
            pLightColor.diffuse += lightAttributes[idx].color.diffuse * ratio;

        }
        
    }
    else
    {
        
    }
}