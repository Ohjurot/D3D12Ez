/*
*   Root Signature Layout (CPU)
*   - 0     float3 "Color"
*   - 1     descriptor tabel "Textures"
*   
*   Root Signature Layout (GPU)
*   - b0        float3 "Color"
*   - t0...     Texture2D<float4> "Textures"
*   - s0        Sampler for "Textures"
*/

#define ROOTSIG \
"RootFlags(ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT)," \
"RootConstants(num32BitConstants=3, b0)," \
"DescriptorTable(" \
    "SRV(t0, numDescriptors = unbounded)" \
")," \
"StaticSampler(s0)"
