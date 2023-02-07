
struct VTX_OUT
{
	float4 vPos : SV_Position;
	float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
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

SamplerState PointSampler : register(s0);
SamplerState LinearSampler : register(s1);
SamplerState AnisotropicSampler : register(s2);


float4 PS_Test(VTX_OUT _in) : SV_Target
{
    float4 color = (float) 0.0f;
    
    color = defaultTexture.Sample(LinearSampler, _in.vUV);
    
	return color;
}