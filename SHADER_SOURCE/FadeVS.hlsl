#include "Global.hlsli"

float4 main( float4 pos : POSITION ) : SV_POSITION
{
    pos.x *= 2;
    pos.y *= 2;
    pos.z = -100;
	return pos;
}