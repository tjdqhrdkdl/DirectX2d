#include "Global.hlsli"

float4 main( float4 pos : POSITION ) : SV_POSITION
{
    pos.x *= 5;
    pos.y *= 5;
    pos.z = -100;
	return pos;
}