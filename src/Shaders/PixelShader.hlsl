#include "RootSignature.hlsl"

float3 puke : register(b0);
Texture2D<float4> textures[] : register(t0);
sampler textureSampler : register(s0);

[RootSignature(ROOTSIG)]
void main(
    // == IN ==
    in float2 uv : Texcoord,

    // == OUT ==
    out float4 pixel : SV_Target
)
{
    float4 texel = textures[0].Sample(textureSampler, uv);
    pixel = float4(texel.rgb * puke, 1.0f);
}
