//------------------------------------------------------------------------------
//  texcube-d3d11.c
//  Texture creation and rendering.
//------------------------------------------------------------------------------

#include <thread>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <atomic>

#define SOKOL_IMPL
#define SOKOL_D3D11
#define SOKOL_D3D11_SHADER_COMPILER

#include "Defines.h"

extern "C" {
	#include "Sokol/d3d11entry.h"
}

#include "ResManAPI/ResourceManager.h"
#include "ResManAPI/FormatLoaders/PNGLoader.h"
#include "ResManAPI/FormatLoaders/JPGLoader.h"
#include "ResManAPI/FormatLoaders/OBJLoader.h"
#include "ResManAPI/FormatLoaders/RMMeshLoader.h"
#include "ResManAPI/FormatLoaders/RMTextureLoader.h"
#include "Sokol/Objects/Model.h"


#include "ziplib/zip.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	// Check for memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Open a debug console window if running in debug mode
//#ifdef _DEBUG
	AllocConsole();
	FILE* a;
	freopen_s(&a, "CONIN$", "r", stdin);
	freopen_s(&a, "CONOUT$", "w", stdout);
	freopen_s(&a, "CONOUT$", "w", stderr);
//#endif

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


	std::ifstream file;
	file.open("Assets/VertShader.hlsl", std::ifstream::in);
	std::string vsString;
	if (file.is_open()) {
		std::stringstream stream;

		stream << file.rdbuf();

		vsString = stream.str();
	}
	else RM_DEBUG_MESSAGE("Couldn't open the vertex shader.", 1);
	file.close();

	file.open("Assets/PixelShader.hlsl", std::ifstream::in);
	std::string psString;
	if (file.is_open()) {
		std::stringstream stream;

		stream << file.rdbuf();

		psString = stream.str();
	}
	else RM_DEBUG_MESSAGE("Couldn't open the pixel shader.", 1);
	file.close();


	sg_shader_desc sgsd{ 0 };
	sgsd.vs.uniform_blocks[0].size = sizeof(vs_params_t);
	sgsd.fs.images[0].type = SG_IMAGETYPE_2D;
	sgsd.vs.source = vsString.c_str();
	sgsd.fs.source = psString.c_str();
    /* create shader */
	sg_shader shd = sg_make_shader(&sgsd);

	/* pipeline object */
	sg_pipeline_desc sgpd{ 0 };
	sgpd.layout.attrs[0].sem_name = "POSITION";
	sgpd.layout.attrs[0].format = SG_VERTEXFORMAT_FLOAT3;
	sgpd.layout.attrs[1].sem_name = "NORMAL";
	sgpd.layout.attrs[1].sem_index = 1;
	sgpd.layout.attrs[1].format = SG_VERTEXFORMAT_FLOAT3;
	sgpd.layout.attrs[2].sem_name = "TEXCOORD";
	sgpd.layout.attrs[2].sem_index = 1;
	sgpd.layout.attrs[2].format = SG_VERTEXFORMAT_FLOAT2;
	sgpd.shader = shd;
	sgpd.index_type = SG_INDEXTYPE_UINT32;
	sgpd.depth_stencil.depth_compare_func = SG_COMPAREFUNC_LESS_EQUAL;
	sgpd.depth_stencil.depth_write_enabled = true;
	sgpd.rasterizer.cull_mode = SG_CULLMODE_NONE;
	sgpd.rasterizer.sample_count = msaa_samples;
	sg_pipeline pip = sg_make_pipeline(&sgpd);

	/* default pass action (clear to gray) */
	sg_pass_action pass_action = { 0 };
	//sg_color_attachment_action sgcaa{ SG_ACTION_CLEAR, 0.f };
	//pass_action.colors[0] = sgcaa;

    /* view-projection matrix */
    hmm_mat4 proj = HMM_Perspective(60.0f, static_cast<float>(width)/static_cast<float>(height), 0.01f, 1000.0f);
	auto camEye = HMM_Vec4(0.0f, 1.5f, 6.0f, 0.f);
	auto camCenter = HMM_Vec3(0.0f, 0.0f, 0.0f);
	auto camUp = HMM_Vec3(0.0f, 1.0f, 0.0f);

    float rx = 0.0f, ry = 0.0f;
	vs_params_t vsParams;
	auto sunDirVec = HMM_Vec4(0.f, -1.f, 0.f, 0.f);
	vsParams.sunDir = sunDirVec;

	// Initialize the resource manager and register the format loaders to it
	ResourceManager &rm = ResourceManager::getInstance();
	rm.init(1024 * 2000);
	rm.registerFormatLoader(RM_NEW(PNGLoader));
	rm.registerFormatLoader(RM_NEW(JPGLoader));
	rm.registerFormatLoader(RM_NEW(OBJLoader));
	rm.registerFormatLoader(RM_NEW(RMMeshLoader));
	rm.registerFormatLoader(RM_NEW(RMTextureLoader));


	sg_draw_state drawState{ 0 };
	drawState.pipeline = pip;

	std::srand(std::time(nullptr));

	Transform sunDir;
	std::vector<Model*> models;
	/*for (int i = 0; i < 2; i++) {
		models.push_back(RM_NEW(Model));
		models.back()->getTransform().translate(HMM_Vec3(0.f, -3.5f + float(i) / 2.5f, -3.f - float(i) * 3.f));
	}*/

	//Model* house = RM_NEW(Model);
	//rm.asyncLoad("Assets/teapot.obj", std::bind(&Model::setMeshNoDeref, house, std::placeholders::_1));
	//rm.asyncLoad("Assets/testImage1.jpg", std::bind(&Model::setTexNoDeref, house, std::placeholders::_1));
	//models.push_back(house);
	//house->getTransform().translate(HMM_Vec3(0.f, -10.f, -20.f));
	//house->getTransform().setScale(HMM_Vec3(10.f, 10.f, 10.f));
	
	/*
		Testcases
	*/
	
	/*
	// Support for all supported formats and loading from zip folders
	*/
	
	/*
	* OBJ
	*/
	models.push_back(RM_NEW(Model));
	auto start = std::chrono::high_resolution_clock::now();
	// OBJ Loading test
	models.back()->setMesh(reinterpret_cast<MeshResource*>(rm.load("Assets/meshes/teapot.obj")));
	models.back()->getTransform().translate(HMM_Vec3(0.f, -100.f, 0.f));
	auto timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
	std::string debugMsg = std::string("Loading of teapot.obj took: " + std::to_string(timeTaken) + "ms.");
	RM_DEBUG_MESSAGE(debugMsg, 0);

	models.push_back(RM_NEW(Model));
	start = std::chrono::high_resolution_clock::now();
	// OBJ in Zip loading test
	models.back()->setMesh(reinterpret_cast<MeshResource*>(rm.load("Assets/AssetsPackage.zip/AssetsPackage/meshes/teapot.obj")));
	models.back()->getTransform().translate(HMM_Vec3(0.f, -100.f, 0.f));
	timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
	debugMsg = std::string("Loading of teapot.obj from zip took: " + std::to_string(timeTaken) + "ms.");
	RM_DEBUG_MESSAGE(debugMsg, 0);

	
	/*
	* RMMesh
	*/
	models.push_back(RM_NEW(Model));
	start = std::chrono::high_resolution_clock::now();
	// RMMesh Loading test
	models.back()->setMesh(reinterpret_cast<MeshResource*>(rm.load("Assets/meshes/teapot.rmmesh")));
	models.back()->getTransform().translate(HMM_Vec3(0.f, -100.f, 0.f));
	timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
	debugMsg = std::string("Loading of teapot.RMMesh took: " + std::to_string(timeTaken) + "ms.");
	RM_DEBUG_MESSAGE(debugMsg, 0);

	models.push_back(RM_NEW(Model));
	start = std::chrono::high_resolution_clock::now();
	// RMMesh in Zip loading test
	models.back()->setMesh(reinterpret_cast<MeshResource*>(rm.load("Assets/AssetsPackage.zip/AssetsPackage/meshes/teapot.rmmesh")));
	models.back()->getTransform().translate(HMM_Vec3(0.f, -100.f, 0.f));
	timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
	debugMsg = std::string("Loading of teapot.RMMesh from zip took: " + std::to_string(timeTaken) + "ms.");
	RM_DEBUG_MESSAGE(debugMsg, 0);


	/*
	* PNG
	*/
	models.push_back(RM_NEW(Model));
	start = std::chrono::high_resolution_clock::now();
	// PNG Loading test
	models.back()->setTexture(reinterpret_cast<TextureResource*>(rm.load("Assets/textures/testImage.png")));
	models.back()->getTransform().translate(HMM_Vec3(0.f, -100.f, 0.f));
	timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
	debugMsg = std::string("Loading of testImage.png took: " + std::to_string(timeTaken) + "ms.");
	RM_DEBUG_MESSAGE(debugMsg, 0);

	models.push_back(RM_NEW(Model));
	start = std::chrono::high_resolution_clock::now();
	// PNG in Zip loading test
	models.back()->setTexture(reinterpret_cast<TextureResource*>(rm.load("Assets/AssetsPackage.zip/AssetsPackage/textures/testImage.png")));
	models.back()->getTransform().translate(HMM_Vec3(0.f, -100.f, 0.f));
	timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
	debugMsg = std::string("Loading of testImage.png from zip took: " + std::to_string(timeTaken) + "ms.");
	RM_DEBUG_MESSAGE(debugMsg, 0);


	/*
	* JPG
	*/
	models.push_back(RM_NEW(Model));
	start = std::chrono::high_resolution_clock::now();
	// JPG Loading test
	models.back()->setTexture(reinterpret_cast<TextureResource*>(rm.load("Assets/textures/testImage1.jpg")));
	models.back()->getTransform().translate(HMM_Vec3(0.f, -100.f, 0.f));
	timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
	debugMsg = std::string("Loading of testImage1.jpg took: " + std::to_string(timeTaken) + "ms.");
	RM_DEBUG_MESSAGE(debugMsg, 0);

	models.push_back(RM_NEW(Model));
	start = std::chrono::high_resolution_clock::now();
	// JPG in Zip loading test
	models.back()->setTexture(reinterpret_cast<TextureResource*>(rm.load("Assets/AssetsPackage.zip/AssetsPackage/textures/testImage1.jpg")));
	models.back()->getTransform().translate(HMM_Vec3(0.f, -100.f, 0.f));
	timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
	debugMsg = std::string("Loading of testImage1.jpg from zip took: " + std::to_string(timeTaken) + "ms.");
	RM_DEBUG_MESSAGE(debugMsg, 0);


	/*
	* RMTex
	*/
	models.push_back(RM_NEW(Model));
	start = std::chrono::high_resolution_clock::now();
	// OBJ Loading test
	models.back()->setTexture(reinterpret_cast<TextureResource*>(rm.load("Assets/textures/testImage1.rmtex")));
	timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
	debugMsg = std::string("Loading of testImage1.rmtex took: " + std::to_string(timeTaken) + "ms.");
	RM_DEBUG_MESSAGE(debugMsg, 0);

	models.push_back(RM_NEW(Model));
	start = std::chrono::high_resolution_clock::now();
	// OBJ in Zip loading test
	models.back()->setTexture(reinterpret_cast<TextureResource*>(rm.load("Assets/AssetsPackage.zip/AssetsPackage/textures/testImage1.rmtex")));
	timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
	debugMsg = std::string("Loading of testImage1.rmtex from zip took: " + std::to_string(timeTaken) + "ms.");
	RM_DEBUG_MESSAGE(debugMsg, 0);




	/*
	*	Thread-safety
	*/
	// Test thread-safety on normal loading
	std::atomic_int aInt = 0;
	int numPtrs = 2;
	std::vector<Resource*> resPtrs(numPtrs);
	auto threadFunc = [&rm, &aInt, &resPtrs](const char* path) {
		resPtrs[aInt++] = rm.load(path);
	};
	std::thread t1(threadFunc, "Assets/meshes/teapot.obj");
	std::thread t2(threadFunc, "Assets/meshes/teapot.rmmesh");
	t1.join();
	t2.join();
	models.push_back(RM_NEW(Model));
	models.back()->setMeshNoDeref(resPtrs[0]);
	models.back()->getTransform().translate(HMM_Vec3(0.f, 0.f, -15.f));
	models.push_back(RM_NEW(Model));
	models.back()->setMeshNoDeref(resPtrs[1]);
	models.back()->getTransform().translate(HMM_Vec3(0.f, -3.f, -15.f));

	// Test thread-safety on async loading
	auto threadAsyncFunc = [&rm, &aInt, &resPtrs](const char* path, std::function<void(Resource*)> callback) {
		rm.asyncLoad(path, callback);
	};
	models.push_back(RM_NEW(Model));
	models.back()->getTransform().translate(HMM_Vec3(2.f, 0.f, -15.f));
	std::thread t3(threadAsyncFunc, "Assets/meshes/cow-normals-test.obj", std::bind(&Model::setMeshNoDeref, models.back(), std::placeholders::_1));
	models.push_back(RM_NEW(Model));
	models.back()->getTransform().translate(HMM_Vec3(-2.f, 0.f, -15.f));
	std::thread t4(threadAsyncFunc, "Assets/meshes/cow-normals.obj", std::bind(&Model::setMeshNoDeref, models.back(), std::placeholders::_1));
	t3.join();
	t4.join();


	// Append a bunch of async asset loading jobs
	models.push_back(RM_NEW(Model));
	models.back()->getTransform().translate(HMM_Vec3(2.f, -3.f, -10.f));
	rm.asyncLoad("Assets/meshes/cow-nonormals.obj", std::bind(&Model::setMeshNoDeref, models.back(), std::placeholders::_1));
	rm.asyncLoad("Assets/textures/testImage.png", std::bind(&Model::setTexNoDeref, models.back(), std::placeholders::_1));
	models.push_back(RM_NEW(Model));
	models.back()->getTransform().translate(HMM_Vec3(-2.f, -3.f, -10.f));
	rm.asyncLoad("Assets/meshes/cow-nonormals.obj", std::bind(&Model::setMeshNoDeref, models.back(), std::placeholders::_1));
	rm.asyncLoad("Assets/textures/testImage1.jpg", std::bind(&Model::setTexNoDeref, models.back(), std::placeholders::_1));
	models.push_back(RM_NEW(Model));
	models.back()->getTransform().translate(HMM_Vec3(2.f, -7.f, -10.f));
	rm.asyncLoad("Assets/meshes/cow-normals.obj", std::bind(&Model::setMeshNoDeref, models.back(), std::placeholders::_1));
	rm.asyncLoad("Assets/textures/testImage.png", std::bind(&Model::setTexNoDeref, models.back(), std::placeholders::_1));

	/*
		End of testcases
	*/

	auto startTime = std::chrono::high_resolution_clock::now();
    while (d3d11_process_events()) {

		/*Extremely simple camera rotation*/
		hmm_mat4 view = HMM_LookAt(HMM_Vec3(camEye.X, camEye.Y, camEye.Z), camCenter, camUp);
		hmm_mat4 view_proj = HMM_MultiplyMat4(proj, view);
		vsParams.vp = view_proj;
		//camEye = HMM_MultiplyMat4ByVec4(HMM_Rotate(1.f, camUp), camEye);

        /* draw frame */
        sg_begin_default_pass(&pass_action, d3d11_width(), d3d11_height());

		sunDir.rotateAroundX(0.3f);
		vsParams.sunDir = HMM_MultiplyMat4ByVec4(sunDir.getMatrix(), sunDirVec);
		
		bool switchModels = false;
		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime) > std::chrono::milliseconds(500)) {
			startTime = std::chrono::high_resolution_clock::now();
			switchModels = true;
		}
		switchModels = false;
		float index = 0.1f;
		for (auto model : models) {
			//model->getTransform().rotateAroundY(5.f);
			model->draw(drawState, vsParams);
			if (switchModels) {
				auto rndVal = std::rand() % 100;
				
				if (rndVal < 10) {
					model->setMesh(reinterpret_cast<MeshResource*>(rm.load("Assets/meshes/cow-normals.obj")));
				}
				else if (rndVal < 50){
					model->setMesh(reinterpret_cast<MeshResource*>(rm.load("Assets/meshes/teapot.obj")));
				}
				else {
					model->setMesh(reinterpret_cast<MeshResource*>(rm.load("Assets/meshes/cow-normals-test.obj")));
				}

				if (rndVal < 30) {
					model->setTexture(reinterpret_cast<TextureResource*>(rm.load("Assets/textures/testImage1.jpg")));
				}
				else if (rndVal < 50) {
					model->setTexture(reinterpret_cast<TextureResource*>(rm.load("Assets/textures/testImage.png")));
				}
				else {
					model->setTexture(reinterpret_cast<TextureResource*>(rm.load("Assets/textures/testFile.png")));
				}
			}
		}

		sg_end_pass();
		sg_commit();
		d3d11_present();
	}

	for (auto m : models) {
		m->~Model();
		::operator delete(m);
	}

	rm.cleanup();
	sg_shutdown();
	d3d11_shutdown();
	return 0;
}
