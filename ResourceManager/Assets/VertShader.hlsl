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
	float4 color: COLOR0;
	float2 uv: TEXCOORD0;
	float4 pos: SV_Position;
};

vs_out main(vs_in inp)
{
    float3 diffuseLightDirection = float3(0.0f, 1.0f, 0.0f);
    float4 diffuseColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
    float diffuseIntensity = 1.0f;
	vs_out outp;
	float4x4 mvp = mul(vp, m);
	inp.pos.w = 1.0f;
    outp.pos = mul(mvp, inp.pos);
	outp.uv = inp.uv;
	//float3 normal = normalize(inp.normal.xyz);
    float lightIntensity = dot(normalize(inp.normal.xyz), sunDir.xyz);
    //float lightIntensity = dot(normalize(-inp.normal.xyz), DiffuseLightDirection);
	outp.color = saturate(diffuseColor * diffuseColor * lightIntensity);
    //outp.color = normalize(-inp.normal);
    //outp.color = float4(lightIntensity, lightIntensity, lightIntensity, 1.0f);
    //outp.color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	return outp;
};