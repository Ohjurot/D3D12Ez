#include "RootSignature.hlsl"

float3 color : register(b0);
Texture2D<float4> textures[] : register(t0);
sampler textureSampler : register(s0);

[RootSignature(ROOTSIG)]
float4 main() : SV_Target
{
    float4 texel = textures[0].Sample(textureSampler, float2(0.5f, 0.5f));
    return float4(texel.rgb, 1.0f);
}
