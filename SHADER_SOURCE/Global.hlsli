
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

Texture2D defaultTexture : register(t0);
//
SamplerState PointSampler : register(s0);
SamplerState LinearSampler : register(s1);
SamplerState AnisotropicSampler : register(s2);

//