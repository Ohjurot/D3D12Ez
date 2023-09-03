#include "RootSignature.hlsl"
#include "Pipeline.hlsli"

Corretion corretion : register(b1);

[RootSignature(ROOTSIG)]
void main(
    // == IN ==
    in float2 pos : Position,
    in float2 uv : Texcoord,

    // == OUT ==
    out float2 o_uv : Texcoord,
    out float4 o_pos : SV_Position
)
{
    // Rules of transformation: Model -> View -> Projection
    float2 px;
    px.x = (pos.x * corretion.cosAngle) - (pos.y * corretion.sinAngle); // Model
    px.y = (pos.x * corretion.sinAngle) + (pos.y * corretion.cosAngle);
    px *= corretion.zoom;           // View
    px.x *= corretion.aspecRatio;   // Projection
    
    o_pos = float4(px, 0.0f, 1.0f);
    o_uv = uv;
}
