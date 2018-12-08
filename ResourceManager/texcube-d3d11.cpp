//------------------------------------------------------------------------------
//  texcube-d3d11.c
//  Texture creation and rendering.
//------------------------------------------------------------------------------

#include <thread>


#define SOKOL_IMPL
#define SOKOL_D3D11
#define SOKOL_D3D11_SHADER_COMPILER
#define SOKOL_LOG(s) OutputDebugStringA(s)

#include "Defines.h"

extern "C" {
	#include "Sokol/d3d11entry.h"
}

#include "ResManAPI/ResourceManager.h"
#include "ResManAPI/FormatLoaders/PNGLoader.h"
#include "ResManAPI/FormatLoaders/JPGLoader.h"
#include "ResManAPI/FormatLoaders/OBJLoader.h"
#include "Sokol/Objects/Model.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	// Check for memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Open a debug console window if running in debug mode
#ifdef _DEBUG
	AllocConsole();
	FILE* a;
	freopen_s(&a, "CONIN$", "r", stdin);
	freopen_s(&a, "CONOUT$", "w", stdout);
	freopen_s(&a, "CONOUT$", "w", stderr);
#endif

	/* setup d3d11 app wrapper and sokol_gfx */
    const int msaa_samples = 4;
    const int width = 800;
    const int height = 600;
    d3d11_init(width, height, msaa_samples, L"Sokol TexCube D3D11");

	sg_desc sgDesc{ 0 };
	sgDesc.d3d11_device = d3d11_device();
	sgDesc.d3d11_device_context = d3d11_device_context();
	sgDesc.d3d11_render_target_view_cb = d3d11_render_target_view;
	sgDesc.d3d11_depth_stencil_view_cb = d3d11_depth_stencil_view;
    sg_setup(&sgDesc);

    /* cube vertex buffer */
    float vertices[] = {
        /* pos                  color                       uvs */
        -1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
         1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f,     1.0f, 0.0f,
         1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f,     1.0f, 1.0f,
        -1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f,     0.0f, 1.0f,

        -1.0f, -1.0f,  1.0f,    0.0f, 1.0f, 0.0f, 1.0f,     0.0f, 0.0f, 
         1.0f, -1.0f,  1.0f,    0.0f, 1.0f, 0.0f, 1.0f,     1.0f, 0.0f,
         1.0f,  1.0f,  1.0f,    0.0f, 1.0f, 0.0f, 1.0f,     1.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,    0.0f, 1.0f, 0.0f, 1.0f,     0.0f, 1.0f,

        -1.0f, -1.0f, -1.0f,    0.0f, 0.0f, 1.0f, 1.0f,     0.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,    0.0f, 0.0f, 1.0f, 1.0f,     1.0f, 0.0f,
        -1.0f,  1.0f,  1.0f,    0.0f, 0.0f, 1.0f, 1.0f,     1.0f, 1.0f,
        -1.0f, -1.0f,  1.0f,    0.0f, 0.0f, 1.0f, 1.0f,     0.0f, 1.0f,

         1.0f, -1.0f, -1.0f,    1.0f, 0.5f, 0.0f, 1.0f,     0.0f, 0.0f,
         1.0f,  1.0f, -1.0f,    1.0f, 0.5f, 0.0f, 1.0f,     1.0f, 0.0f,
         1.0f,  1.0f,  1.0f,    1.0f, 0.5f, 0.0f, 1.0f,     1.0f, 1.0f,
         1.0f, -1.0f,  1.0f,    1.0f, 0.5f, 0.0f, 1.0f,     0.0f, 1.0f,

        -1.0f, -1.0f, -1.0f,    0.0f, 0.5f, 1.0f, 1.0f,     0.0f, 0.0f,
        -1.0f, -1.0f,  1.0f,    0.0f, 0.5f, 1.0f, 1.0f,     1.0f, 0.0f,
         1.0f, -1.0f,  1.0f,    0.0f, 0.5f, 1.0f, 1.0f,     1.0f, 1.0f,
         1.0f, -1.0f, -1.0f,    0.0f, 0.5f, 1.0f, 1.0f,     0.0f, 1.0f,

        -1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.5f, 1.0f,     0.0f, 0.0f,
        -1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.5f, 1.0f,     1.0f, 0.0f,
         1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.5f, 1.0f,     1.0f, 1.0f,
         1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.5f, 1.0f,     0.0f, 1.0f
    };

	sg_buffer_desc sgVbd{ 0 };
	sgVbd.type = SG_BUFFERTYPE_VERTEXBUFFER;
	sgVbd.size = sizeof(vertices);
	sgVbd.content = vertices;
    sg_buffer vbuf = sg_make_buffer(&sgVbd);

    /* create an index buffer for the cube */
    uint16_t indices[] = {
        0, 1, 2,  0, 2, 3,
        6, 5, 4,  7, 6, 4,
        8, 9, 10,  8, 10, 11,
        14, 13, 12,  15, 14, 12,
        16, 17, 18,  16, 18, 19,
        22, 21, 20,  23, 22, 20
    };

	sg_buffer_desc sgIbd{ 0 };
	sgIbd.type = SG_BUFFERTYPE_INDEXBUFFER;
	sgIbd.size = sizeof(indices);
	sgIbd.content = indices;
    sg_buffer ibuf = sg_make_buffer(&sgIbd);

    /* create a checkerboard texture */
    uint32_t pixels[4*4] = {
        0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
        0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
        0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
        0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
    };


	/*std::ifstream vs_stream;
	size_t vs_size;
	char* vs_data;

	vs_stream.open(vsCompiledPath, std::ifstream::in | std::ifstream::binary);
	if (vs_stream.good())
	{
		vs_stream.seekg(0, ios::end);
		vs_size = size_t(vs_stream.tellg());
		vs_data = new char[vs_size];
		vs_stream.seekg(0, ios::beg);
		vs_stream.read(&vs_data[0], vs_size);
		vs_stream.close();

		result = device->CreateVertexShader(&vs_data, vs_size, 0, &m_vertexShader);
		if (FAILED(result))
		{
			return false;
		}
	}
	else
	{
		return false;
	}*/

	sg_shader_desc sgsd{ 0 };
	sgsd.vs.uniform_blocks[0].size = sizeof(vs_params_t);
	sgsd.fs.images[0].type = SG_IMAGETYPE_2D;
	sgsd.vs.source =
		"cbuffer params: register(b0) {\n"
		"  float4x4 m;\n"
		"  float4x4 vp;\n"
		"};\n"
		"struct vs_in {\n"
		"  float4 pos: POSITION;\n"
		//"  float4 color: COLOR1;\n"
		//"  float2 uv: TEXCOORD1;\n"
		"};\n"
		"struct vs_out {\n"
		"  float4 color: COLOR0;\n"
		//"  float2 uv: TEXCOORD0;\n"
		"  float4 pos: SV_Position;\n"
		"};\n"
		"vs_out main(vs_in inp) {\n"
		"  vs_out outp;\n"
		"  float4x4 mvp = mul(vp, m);\n"
		"  inp.pos.w = 1.0f;\n"
		"  outp.pos = mul(mvp, inp.pos);\n"
		"  outp.color = float4(1.0f, 1.0f, 1.0f, 1.0f);\n"
		//"  outp.uv = inp.uv;\n"
		"  return outp;\n"
		"};\n";
	sgsd.fs.source =
		//"Texture2D<float4> tex: register(t0);\n"
		//"sampler smp: register(s0);\n"
		"float4 main(float4 color: COLOR0): SV_Target0 {\n"
		//"float4 main(float4 color: COLOR0, float2 uv: TEXCOORD0): SV_Target0 {\n"
		"  return color;\n"
		//"  return tex.Sample(smp, uv) * color;\n"
		"}\n";
    /* create shader */
	sg_shader shd = sg_make_shader(&sgsd);

	/* pipeline object */
	sg_pipeline_desc sgpd{ 0 };
	sgpd.layout.attrs[0].sem_name = "POSITION";
	sgpd.layout.attrs[0].format = SG_VERTEXFORMAT_FLOAT3;
	/*sgpd.layout.attrs[1].sem_name = "COLOR";
	sgpd.layout.attrs[1].sem_index = 1;
	sgpd.layout.attrs[1].format = SG_VERTEXFORMAT_FLOAT4;
	sgpd.layout.attrs[2].sem_name = "TEXCOORD";
	sgpd.layout.attrs[2].sem_index = 1;
	sgpd.layout.attrs[2].format = SG_VERTEXFORMAT_FLOAT2;*/
	sgpd.shader = shd;
	sgpd.index_type = SG_INDEXTYPE_UINT32;
	sgpd.depth_stencil.depth_compare_func = SG_COMPAREFUNC_LESS_EQUAL;
	sgpd.depth_stencil.depth_write_enabled = true;
	sgpd.rasterizer.cull_mode = SG_CULLMODE_NONE;
	sgpd.rasterizer.sample_count = msaa_samples;
	sg_pipeline pip = sg_make_pipeline(&sgpd);

	/* default pass action (clear to gray) */
	sg_pass_action pass_action = { 0 };

    /* view-projection matrix */
    hmm_mat4 proj = HMM_Perspective(60.0f, static_cast<float>(width)/static_cast<float>(height), 0.01f, 1000.0f);
    hmm_mat4 view = HMM_LookAt(HMM_Vec3(0.0f, 1.5f, 6.0f), HMM_Vec3(0.0f, 0.0f, 0.0f), HMM_Vec3(0.0f, 1.0f, 0.0f));
    hmm_mat4 view_proj = HMM_MultiplyMat4(proj, view);

    float rx = 0.0f, ry = 0.0f;
	vs_params_t vsParams;
	vsParams.vp = view_proj;


	// Initialize the resource manager and register the format loaders to it
	ResourceManager &rm = ResourceManager::getInstance();
	rm.init(1024 * 300);
	rm.registerFormatLoader(RM_NEW(PNGLoader));
	rm.registerFormatLoader(RM_NEW(JPGLoader));
	rm.registerFormatLoader(RM_NEW(OBJLoader));


	Model model1(reinterpret_cast<MeshResource*>(rm.load("Assets/teapot.obj")), reinterpret_cast<TextureResource*>(rm.load("Assets/testImage.png")), pip);
    while (d3d11_process_events()) {
        /* draw frame */
        sg_begin_default_pass(&pass_action, d3d11_width(), d3d11_height());

		model1.draw(vsParams);
		model1.getTransform().rotateAroundX(1.0f);
		//model1.getTransform().translate(HMM_Vec3(0.0f, 0.0f, -1.0f));

        /*sg_apply_draw_state(&draw_state);

		transform1.rotateAroundX(2.f);
		transform1.rotateAroundY(-4.f);
		vs_params.mvp = HMM_MultiplyMat4(view_proj, transform1.getMatrix());
        sg_apply_uniform_block(SG_SHADERSTAGE_VS, 0, &vs_params, sizeof(vs_params));
        sg_draw(0, 36, 1);

		transform2.rotateAroundX(0.1f);
		transform2.rotateAroundY(0.2f);
		vs_params.mvp = HMM_MultiplyMat4(view_proj, transform2.getMatrix());
		sg_apply_uniform_block(SG_SHADERSTAGE_VS, 0, &vs_params, sizeof(vs_params));
		sg_draw(0, 36, 1);*/

        sg_end_pass();
        sg_commit();
        d3d11_present();
    }
    sg_shutdown();
    d3d11_shutdown();
    return 0;
}
