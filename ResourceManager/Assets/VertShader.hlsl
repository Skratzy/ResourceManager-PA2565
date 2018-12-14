cbuffer params: register(b0) {
	float4x4 m;
	float4x4 vp;
    float4 sunDir;
};

struct vs_in {
	float4 pos: POSITION;
	float4 normal: NORMAL1;
	float2 uv: TEXCOORD1;
};

struct vs_out {
    float4 color : COLOR0;
	float2 uv: TEXCOORD0;
	float4 pos: SV_Position;
};

vs_out main(vs_in inp)
{
	vs_out outp;
	float4x4 mvp = mul(vp, m);
	inp.pos.w = 1.0f;
    outp.pos = mul(mvp, inp.pos);
	outp.uv = inp.uv;
	
    float3 midDayLightDir = float3(0.0f, 1.0f, 0.0f);
    float3 lightDir = midDayLightDir - sunDir.xyz;
    float r = abs(lightDir.y) * 0.8f;
    float g = abs(lightDir.y) * 0.5f;
    float b = abs(lightDir.z) * 0.5f;

    float4 color = float4(r, g, b, 1.0f);
    float3 normal = mul(inp.normal, m).xyz;
    float lightIntensity = saturate(dot(normalize(normal), normalize(-sunDir.xyz)));

    outp.color = saturate(color * lightIntensity);
	return outp;
};