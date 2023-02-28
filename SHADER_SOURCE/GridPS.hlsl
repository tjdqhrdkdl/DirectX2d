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
    
};

float4 Main(VTX_OUT In) : SV_TARGET
{
    float4 Out = float4(1.0f, 1.0f, 1.0f, 1.0f);
    
    const int width = 100;
    const int height = 100;
    
    uint worldX = (int) In.vPos.x;
    uint worldY = (int) In.vPos.y;
    
    // ¼± µÎ²²
    const float thickness = 1.0f;
    
    if (abs((worldX + 1) % (width + cbiData*5)) <= thickness)
        return Out;
    
    if (abs((worldY) % (height+cbiData*5)) <= thickness)
        return Out;
    
    discard;
    return float4(1.0f, 0.0f, 1.0f, 1.0f);
}