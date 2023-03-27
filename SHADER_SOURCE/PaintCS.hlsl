
RWTexture2D<float4> tex : register(u0);

[numthreads(32, 32, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
    if (1024 <= DTid.x || 1024 <= DTid.y)
    {
        return;
    }
    
    tex[DTid.xy] = float4(0.0f, 0.0f, 1.0f, 1.0f);
    
}