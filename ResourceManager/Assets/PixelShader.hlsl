Texture2D<float4> tex: register(t0);
sampler smp: register(s0);

float4 main(float4 color: COLOR0, float2 uv: TEXCOORD0): SV_Target0 {
	float4 ambientColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
	float ambientIntensity = 0.1f;
    return saturate(tex.Sample(smp, uv) * color + ambientColor * ambientIntensity);
	//return color;
};