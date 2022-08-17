//
//                      _oo0oo_
//                     o8888888o
//                     88" . "88
//                     (| -_- |)
//                     0\  =  /0
//                   ___/`---'\___
//                 .' \\|     |# '.
//                / \\|||  :  |||# \
//               / _||||| -:- |||||- \
//              |   | \\\  -  #/ |   |
//              | \_|  ''\---/''  |_/ |
//              \  .-\__  '-'  ___/-. /
//            ___'. .' / --.--\  `. .'___
//         ."" '<  `.___\_<|>_/___.' >' "".
//        | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//        \  \ `_.   \_ __\ /__ _/   .-` /  /
//    =====`-.____`.___ \_____/___.-`___.-'=====
//                      `=---='
//    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//				 佛祖保佑	    	 永无BUG
#define GLEW_STATIC
//load images
#include "Model.h"
#include "SkyBox.h"
#include <filesystem>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "fstream"
#include "sstream"
#include "imgui.h"
#include "imgui_impl_glfw.h"

#include "imgui_impl_opengl3.h"
#include "Camera.h"
#include "FrameBuffer.h"
#include "Material.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Core.h"
#include "stb_image.h"
#include "My.h"
class LightSpot;

#pragma region Camera&Input
// ---------------------------------*相机*---------------------------------
Camera camera(glm::vec3(0, 5.0f, -10.0f), glm::radians(0.0f), glm::radians(0.0f), glm::vec3(0, 1.0f, 0));

// ---------------------------------*鼠标*---------------------------------

void mouse_callback(GLFWwindow* window, double xPos, double yPos);
//上一次鼠标的x和y坐标
float lastX = 960;
float lastY = 540;
bool firstMouse = true;

void processInput(GLFWwindow* window);

#pragma endregion

// #################################*MAIN*######################################
int main(int argc, char* argv[])
{

	std::string exePath = argv[0];

#pragma region Open Window & Set mouse
	//初始化
	glfwInit();
	//主版本号3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//副版本号3，所以版本是3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//用core_profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//创建一个window指针变量
	GLFWwindow* window = glfwCreateWindow(1920, 1080, "MyOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "打开窗口失败" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//Initial GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Initial GLEW failed" << std::endl;
		glfwTerminate();
		return -1;
	}

	// ---------------------------------*Settings*---------------------------------
	float ScreenWidth = 2560.0f;
	float ScreenHeight = 1440.0f;
	glViewport(0, 0, ScreenWidth, ScreenHeight);
	//HDR
	float exposure = 1.0f;

	//Z_BUFFER
	glEnable(GL_DEPTH_TEST);
	/////Cull
	//glEnable(GL_CULL_FACE);
	//gamma
	//glEnable(GL_FRAMEBUFFER_SRGB);
	//HDR
	//disable VSync.
	glfwSwapInterval(0);
	// 修复预滤波贴图的接缝脱节
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

#pragma endregion
#pragma region Init Shader Program
	// ---------------------------------*Shader*---------------------------------
	Shader* equalRectTOCubeShader = new Shader("resources/shaders/equalRectVS.glsl",
	                                   "resources/shaders/equalRectFRAG.glsl");
	Shader* irradianceMapShader = new Shader("resources/shaders/equalRectVS.glsl",
	                                 "resources/shaders/irradianceMapFRAG.glsl");
	Shader* preFilterShader = new Shader("resources/shaders/equalRectVS.glsl", "resources/shaders/preFilterFRAG.glsl");
	Shader* genBrdfLutShader = new Shader("resources/shaders/genBrdfLutVS.glsl",
		"resources/shaders/genBrdfLutFRAG.glsl");


	Shader* sceneShader = new Shader("resources/shaders/vertexShader.glsl", "resources/shaders/fragmentShader.glsl");
	Shader* changeShader = new Shader("resources/shaders/changeVS.glsl", "resources/shaders/changeFRAG.glsl",
		"resources/shaders/changeGS.glsl");
	Shader* screenShader = new Shader("resources/shaders/screenVertexShader.glsl",
		"resources/shaders/screenFragmentShader.glsl");
	Shader* skyBoxShader = new Shader("resources/shaders/skyBoxVertexShader.glsl",
		"resources/shaders/skyBoxFragmentShader.glsl");
	Shader* normalVisualizeShader = new Shader("resources/shaders/NVisualizeVertex.glsl",
		"resources/shaders/NVisualizeFragment.glsl",
		"resources/shaders/NVisualizeGeometry.glsl");
	Shader* simpleDepthShader = new Shader("resources/shaders/simpleDepthShaderVS.glsl",
		"resources/shaders/simpleDepthFRAG.glsl");
	Shader* debugDepth = new Shader("resources/shaders/debugDepthVS.glsl", "resources/shaders/debugDepthFRAG.glsl");
	Shader* HdrShader = new Shader("resources/shaders/HdrVS.glsl", "resources/shaders/HdrFRAG.glsl");
	Shader* gaussianBlurShader = new Shader("resources/shaders/gaussianBlurVS.glsl",
		"resources/shaders/gaussianBlurFRAG.glsl");
	Shader* standardShader = new Shader("resources/shaders/standardVS.glsl", "resources/shaders/standardFRAG.glsl");

	Shader* skyBoxHDRShader = new Shader("resources/shaders/skyBoxHDRVS.glsl", "resources/shaders/skyBoxHDRFRAG.glsl");
	Shader* DEBUGSKYBOX = new Shader("resources/shaders/DEBUGshowSkyboxVS.glsl",
		"resources/shaders/DEBUGshowSkyboxFRAG.glsl");
	Shader* Aurora = new Shader("resources/shaders/debugDepthVS.glsl", "resources/shaders/auroraFRAG.glsl");



#pragma endregion
	// ---------------------------------*Material*---------------------------------
	//这里先初始化一下，在render循环里再给想要的值
	Material* material = new Material;
	material = new Material(standardShader
	);


	//---------------------------------*SkyBox*---------------------------------
	SkyBox skyBox;
	skyBox.set(skyBoxShader, sceneShader);



	std::vector<std::string> faces
	{
		"resources/textures/skyBox_right.png",
		"resources/textures/skyBox_left.png",
		"resources/textures/skyBox_up.png",
		"resources/textures/skyBox_down.png",
		"resources/textures/skyBox_front.png",
		"resources/textures/skyBox_back.png",
	};
	unsigned int skyboxCubeMap = skyBox.loadCubmap(faces);


#pragma region Light Declare
	// ---------------------------------*Light*---------------------------------
	LightDirectional* light_directional = new LightDirectional(
		//position
		glm::vec3(0, 0, -30.0f),
		//angle
		glm::vec3(0.0f, 0.0f, 0.0f),
		//color
		glm::vec3(1.0f, 1.0f, 1.0f),
		//intensity
		float(1.0f)
	);

	LightPoint* light_point0 = new LightPoint(
		glm::vec3(1.0f, 0, 0),
		glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
		glm::vec3(1.0f, 0, 0)
	);
	LightPoint* light_point1 = new LightPoint(
		glm::vec3(0, 1.0f, 0),
		glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
		glm::vec3(0, 1.0f, 0)
	);

	LightSpot* light_spot = new LightSpot(
		glm::vec3(0, 30.0f, 0),
		glm::vec3(glm::radians(90.0f), 0, 0),
		glm::vec3(1.0f, 1.0f, 1.0f)
	);


	// lights
	// ------
	glm::vec3 lightPositions[] = {
		glm::vec3(0.0f, 0.0f, 10.0f),
	};
	glm::vec3 lightColors[] = {
		glm::vec3(150.0f, 150.0f, 150.0f),
	};


#pragma endregion


	//Model model(
	//	exePath.substr(0, exePath.find_last_of('\\')) + "\\" + "Models" + "\\" + "knight-artorias" + "\\" + "Artorias.obj");
	Model sphere(
		exePath.substr(0, exePath.find_last_of('\\')) + "\\" + "Models" + "\\" + "Sphere" + "\\" + "Sphere" + "\\" +
		"21" + "\\" + "Sphere.obj");

	//Model sphere(
	//	exePath.substr(0, exePath.find_last_of('\\')) + "\\" + "Models" + "\\" + "Sphere" + "\\" + "Sphere.obj");
	Model CerberusGun(exePath.substr(0, exePath.find_last_of('\\')) + "\\" + "Models" + "\\" + "Cerberus" + "\\" + "Cerberus.obj");
	//Model model(
	//	exePath.substr(0, exePath.find_last_of('\\')) + "\\" + "Models" + "\\" + "nevermore" + "\\"  + "shadow_fiend_econ.fbx");
	Model testScene(exePath.substr(0, exePath.find_last_of('\\')) + "\\" + "Models" + "\\" + "cz" + "\\" + "all.obj");
	Model bricks(exePath.substr(0, exePath.find_last_of('\\')) + "\\" + "Models" + "\\" + "TestBox" + "\\" + "testBox.obj");
	//Model bricks(exePath.substr(0, exePath.find_last_of('\\')) + "\\" + "Models" + "\\" + "Bricks" + "\\" + "bricks.obj");

	//// ---------------------------------*ImGUI*---------------------------------
	//// Setup Dear ImGui context
	//IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;

	// ---------------------------------*FrameBuffer*---------------------------------
	// Texture for Shadow Map FBO
	unsigned int quadVAO;
	quadVAO = Core::getQuadVAO();

	// ---------------------------------*FrameBuffer*---------------------------------
	//TODO 把后处理的FBO都放在一起
	unsigned int  postrocessingColorBuffer, bloomColorBuffer, postprocessingFbo, postprocessingRbo;
	//////////////set
	//生成并绑定FBO
	glGenFramebuffers(1, &postprocessingFbo);
	glBindFramebuffer(GL_FRAMEBUFFER, postprocessingFbo);
	//生成纹理附件
	glGenTextures(1, &postrocessingColorBuffer);
	glBindTexture(GL_TEXTURE_2D, postrocessingColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, ScreenWidth, ScreenHeight, 0, GL_RGB, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	//附加到FBO上
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, postrocessingColorBuffer, 0);

	//生成纹理附件
	glGenTextures(1, &bloomColorBuffer);
	glBindTexture(GL_TEXTURE_2D, bloomColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, ScreenWidth, ScreenHeight, 0, GL_RGB, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, bloomColorBuffer, 0);
	unsigned int bloomAttachment[2] = { GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, bloomAttachment);

	//生成并绑定RBO
	glGenRenderbuffers(1, &postprocessingRbo);
	glBindRenderbuffer(GL_RENDERBUFFER, postprocessingRbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, ScreenWidth, ScreenHeight);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	//接下来，作为完成帧缓冲之前的最后一步，我们将渲染缓冲对象附加到帧缓冲的深度和模板附件上：
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, postprocessingRbo);
	//记得要解绑帧缓冲，保证我们不会不小心渲染到错误的帧缓冲上。
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	// ---------------------------------*ShadowMap*---------------------------------
	// Framebuffer for Shadow Map
	GLuint* shadowMapFBO = new GLuint;
	GLuint* shadowMap = new GLuint;
	GLsizei shadowMapWidth = 2048.0f;
	GLsizei shadowMapHeight = 2048.0f;
	Core::getShdowFboMap(shadowMapFBO, shadowMap, shadowMapWidth, shadowMapHeight);

	// ---------------------------------*PingPongBuffer*---------------------------------
	unsigned int pingpongFBO[2];
	unsigned int pingpongColorBuffers[2];
	glGenFramebuffers(2, pingpongFBO);
	glGenTextures(2, pingpongColorBuffers);
	for (unsigned int i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
		glBindTexture(GL_TEXTURE_2D, pingpongColorBuffers[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, ScreenWidth, ScreenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//这里用clamp是防止模糊的时候采样到了重复的像素，如果不clamp边界外就是repeat的。
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorBuffers[i], 0);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "pingpong Framebuffer" << i << "not complete!" << std::endl;
	}

#pragma region 

	// ---------------------------------*PBR 预处理*---------------------------------
	//漫反射部分
	GLuint* cubemapFromHDR = new GLuint;
	GLuint* irradianceMap = new GLuint;
	//镜面反射部分的贴图
	GLuint* brdfLUTTexture = new GLuint;
	GLuint* prefilterMap = new GLuint;
	Core::getIndirectDiffuseMaps(cubemapFromHDR, irradianceMap,equalRectTOCubeShader,irradianceMapShader);
	Core::getIndirectSpecularMaps(prefilterMap, brdfLUTTexture, cubemapFromHDR,preFilterShader,genBrdfLutShader);

	//Cull
	glEnable(GL_CULL_FACE);
	#pragma region 
	// ---------------------------------*Flags*---------------------------------
	float ao = 1.0f;
	bool mouseFlag = false;
	static int clicked = 0;
	static int fboClicked = 0;
	static int showNormalClicked = 0;
	static int shadowMapFlagClicked = 0;
	static int hieghtMapFlagClicked = 0;
	static int hdrFlagClicked = 0;
	bool fboFlag = false;
	bool showNormal = false;
	bool shadowMapFlag = false;
	bool heightMapFlag = false;
	bool hdrFlag = false;
	static bool show_app_metrics = true;

	#pragma endregion Flags
	//---------------------------------*SHADER setup*---------------------------------

	sceneShader->use();

	sceneShader->PassUniformToShader("shadowMap", 5);
	changeShader->use();
	changeShader->PassUniformToShader("shadowMap", 5);
	HdrShader->use();
	HdrShader->PassUniformToShader("screenTexture", 0);
	HdrShader->PassUniformToShader("bloomBlur", 1);
	gaussianBlurShader->use();
	gaussianBlurShader->PassUniformToShader("screenTexture", 0);

	standardShader->use();
	standardShader->PassUniformToShader("prefilterMap", 8);
	standardShader->PassUniformToShader("brdfLUT", 7);
	standardShader->PassUniformToShader("irradianceMap", 6);
	standardShader->PassUniformToShader("shadowMap", 9);
	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *prefilterMap);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, *brdfLUTTexture);
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *irradianceMap);


	skyBoxHDRShader->use();
	skyBoxHDRShader->PassUniformToShader("environmentMap", 0);
	DEBUGSKYBOX->use();
	DEBUGSKYBOX->PassUniformToShader("environmentMap", 0);


	// #################################*渲染循环*######################################
	while (!glfwWindowShouldClose(window))
	{
		// 1. 先画GUI
		//---------------------------------*ImGUI*---------------------------------
		#pragma region IMGUI
		// Poll and handle events (inputs, window resize, etc.)
		glfwPollEvents();
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);
		//开始菜单
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Quit", "Alt+F4")) break;
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("TODO")) {
					//do something
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		
			ImGui::MenuItem("Metrics/Debugger", NULL, &show_app_metrics);
			if (show_app_metrics)
				ImGui::ShowMetricsWindow(&show_app_metrics);

			ImGui::Begin("inspector"); // Create a window called "Hello, world!" and append into it.
			ImGui::Text("My Owen Render Demo v0.0.1");
			ImGui::Text("Application average (%.0f FPS)", ImGui::GetIO().Framerate);
			ImGui::Text("Application average (%.2f MS)", 1000.0f/ImGui::GetIO().Framerate);
			
			if (ImGui::Button("LineMode"))
				clicked++;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			if (clicked & 1)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}

			ImGui::SameLine();

			if (ImGui::Button("Bloom"))
				fboClicked++;
			fboFlag = false;
			if (fboClicked & 1)
			{
				fboFlag = true;
			}

			ImGui::SameLine();

			if (ImGui::Button("showNormal"))
				showNormalClicked++;
			showNormal = false;
			if (showNormalClicked & 1)
			{
				showNormal = true;
			}

			ImGui::SameLine();

			if (ImGui::Button("Shadow"))
				shadowMapFlagClicked++;
			shadowMapFlag = false;
			if (shadowMapFlagClicked & 1)
			{
				shadowMapFlag = true;
			}

			ImGui::SameLine();
			if (ImGui::Button("HDR"))
				fboClicked++;
			fboFlag = false;
			if (fboClicked & 1)
			{
				fboFlag = true;
			}

			ImGui::Text("DirLight:");
			ImGui::SliderFloat("DirLight Intensity", &light_directional->intensity, 0.0f, 5.0f);
			// Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("DirLigh Ccolor", (float*)&light_directional->color);
			// Edit 3 floats representing a color
			ImGui::SliderFloat3("LightDirection", (float*)&light_directional->angles, -360, 360);
			ImGui::SliderFloat3("LightPosition", (float*)&light_directional->position, -360, 360);
			ImGui::Spacing();

			ImGui::Text("Model:");
			ImGui::SliderFloat3("ModelRotation", (float*)&sphere.angles, -360.0f, 360.0f);
			ImGui::SliderFloat("ModelScale", (float*)&sphere.scale, 0, 10.0f);
			ImGui::SliderFloat3("ModelTranslate", (float*)&sphere.translate, -100, 100);

			ImGui::Text("Scene:");
			ImGui::InputFloat3("SceneRotation", (float*)&testScene.angles);
			ImGui::SliderFloat("SceneScale", (float*)&testScene.scale, 0, 10.0f);
			ImGui::InputFloat3("SceneTranslate", (float*)&testScene.translate);


			ImGui::SliderFloat("exposure ", (float*)&exposure, 0.001, 10.0f);
			//这里记得要更新direction，因为们是传direction到shader，而angles的值在初始化的时候就定了，然后马上会调用这个函数去更新方向，
			//所以如果不在这里再次更新方向，那angles的值就算用指针变了，但是他不会更新成direction。
			light_directional->UpdateDirection();
			ImGui::Text("PBR:");
			ImGui::SliderFloat("AO", (float*)&ao, 0, 1.0f);

			ImGui::End();
		




		//// 3. Show another simple window.
		//if (show_another_window)
		//{
		//	ImGui::Begin("Another Window", &show_another_window);
		//	// Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		//	ImGui::Text("Hello from another window!");
		//	if (ImGui::Button("Close Me"))
		//		show_another_window = false;
		//	ImGui::End();
		//}


#pragma endregion
		// 2. 监测用户输入，开始鼠标的回调
		//---------------------------------*用户输入*---------------------------------`
		//检测用户输入的信息并进行操作
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			//注册回调函数
			//一旦鼠标移动，就会检测到x和y给值给mouse_callback
			glfwSetCursorPosCallback(window, mouse_callback);
			bool firstMouse = true;
			//控制相机移动的函数在这里
			processInput(window);
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
		{
			//显示鼠标
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			//鼠标回调NULL
			glfwSetCursorPosCallback(window, NULL);
			//让下一次点击屏幕不会移动相机
			firstMouse = true;
		}


		// 2.给主要的渲染shader赋予参数，包括MVP、灯光、相机等
		// ---------------------------------*MVP矩阵*---------------------------------
		//声明
		glm::mat4 view, projection, modelMat;
		//赋值
		modelMat = glm::rotate(modelMat, glm::radians(sphere.angles.x), glm::vec3(1.0f, 0.0f, 0));
		modelMat = glm::rotate(modelMat, glm::radians(sphere.angles.y), glm::vec3(0.0f, 1.0f, 0));
		modelMat = glm::rotate(modelMat, glm::radians(sphere.angles.z), glm::vec3(0.0f, 0, -1.0f));
		modelMat = glm::scale(modelMat, glm::vec3(sphere.scale.x, sphere.scale.x, sphere.scale.x));
		modelMat = glm::translate(modelMat, sphere.translate);
		view = camera.GetViewMatrix();
		projection = glm::perspective(glm::radians(45.0f), ScreenWidth / ScreenHeight, 0.1f, 750.0f);
		//scene model
		glm::mat4 sceneModelMat;
		testScene.translate = glm::vec3(140.0f, -24.0f, 525.0f);

		sceneModelMat = glm::scale(sceneModelMat, glm::vec3(3.0f, 3.0f, 3.0f));
		sceneModelMat = glm::translate(sceneModelMat, testScene.translate);


		sceneShader->use(); //这里要记得切到主shader，记住opengl是个状态机
		sceneShader->PassMat4ToShader("model", modelMat);
		sceneShader->PassMat4ToShader("view", view);
		sceneShader->PassMat4ToShader("projection", projection);
		// ---------------------------------*材质*---------------------------------
		//DIRECTIONAL LIGHT
		sceneShader->PassUniformToShader("lightD.pos", light_directional->position);
		sceneShader->PassUniformToShader("lightD.color", light_directional->color);
		sceneShader->PassUniformToShader("lightD.dirToLight", light_directional->direction);
		sceneShader->PassUniformToShader("lightD.intensity", light_directional->intensity);
		//POINT LIGHT
		sceneShader->PassUniformToShader("lightP0.pos", light_point0->position);
		sceneShader->PassUniformToShader("lightP0.color", light_point0->color);
		sceneShader->PassUniformToShader("lightP0.dirToLight", light_point0->lightDir);
		sceneShader->PassUniformToShader("lightP0.constant", light_point0->constant);
		sceneShader->PassUniformToShader("lightP0.linear", light_point0->linear);
		sceneShader->PassUniformToShader("lightP0.quadratic", light_point0->quadratic);
		//SPOT LIGHT
		sceneShader->PassUniformToShader("spotLight.cosPhiInner", light_spot->cosPhiInner);
		sceneShader->PassUniformToShader("spotLight.cosPhiOuter", light_spot->cosPhiOuter);
		sceneShader->PassUniformToShader("spotLight.pos", light_spot->position);
		sceneShader->PassUniformToShader("spotLight.color", light_spot->color);
		sceneShader->PassUniformToShader("spotLight.dirToLight", light_spot->direction);
		sceneShader->PassUniformToShader("spotLight.constant", light_spot->constant);
		sceneShader->PassUniformToShader("spotLight.linear", light_spot->linear);
		sceneShader->PassUniformToShader("spotLight.quadratic", light_spot->quadratic);
		//CAMERA
		sceneShader->PassUniformToShader("cameraPos", camera.Position);
		////material
		//sceneShader->PassUniformToShader("material.ambient", material->ambient);
		//sceneShader->PassUniformToShader("material.specular", Shader::SPECULAR);
		//sceneShader->PassUniformToShader("material.diffuse", Shader::DIFFUSE);
		//sceneShader->PassUniformToShader("material.emission", Shader::EMISSION);
		//sceneShader->PassUniformToShader("material.reflection", Shader::Reflection);
		//sceneShader->PassUniformToShader("material.shininess", material->shininess);

		//pass uniform nano suit 
		changeShader->use(); //这里要记得切到主shader，记住opengl是个状态机
		changeShader->PassMat4ToShader("model", modelMat);
		changeShader->PassMat4ToShader("view", view);
		changeShader->PassMat4ToShader("projection", projection);
		// ---------------------------------*材质*---------------------------------
		//DIRECTIONAL LIGHT
		changeShader->PassUniformToShader("lightD.pos", light_directional->position);
		changeShader->PassUniformToShader("lightD.color", light_directional->color);
		changeShader->PassUniformToShader("lightDirection", light_directional->direction);
		changeShader->PassUniformToShader("lightD.intensity", light_directional->intensity);
		//CAMERA
		changeShader->PassUniformToShader("cameraPosition", camera.Position);
		////material
		//changeShader->PassUniformToShader("material.ambient", material->ambient);
		//changeShader->PassUniformToShader("material.specular", Shader::SPECULAR);
		//changeShader->PassUniformToShader("material.diffuse", Shader::DIFFUSE);
		//changeShader->PassUniformToShader("material.emission", Shader::EMISSION);
		//changeShader->PassUniformToShader("material.reflection", Shader::Reflection);
		//changeShader->PassUniformToShader("material.shininess", 256.0f);


		// 3.后处理的FBO，如果fboFlag==true，就会把fbo绑定到GL_FRAMEBUFFER上，并激活，之后画的东西
		//都会在这个GL_FRAMEBUFFER也就是fbo上
		// ---------------------------------*framebuffer*---------------------------------
		//postProcessing
		//bind to framebuffer
		if (fboFlag)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, postprocessingFbo);
		}
		glEnable(GL_DEPTH_TEST);
		// 4.把屏幕清掉（此时清楚的是上一帧的内容），开始记录到fbo上
		glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// 5.从灯光的视角渲染场景，把场景的深度记录到shadowmapFBO的depthMap上
		// ---------------------------------*shadowMap*---------------------------------
		// Matrices needed for the light's perspective
		//灯光视角的投影矩阵，构建的是一个标准立方体
		glm::mat4 orthgonalProjection = glm::ortho(-35.0f, 35.0f, -35.0f, 35.0f, 0.1f, 1000.0f);
		//灯光视角的model矩阵,用来控制深度图和灯光方向一致
		glm::mat4 lightModel = glm::mat4(1.0f);
		//这里的X要绕着负的x轴转，看起来才是对的，根据图形学第一定律，就这样不改了
		lightModel = glm::rotate(lightModel, glm::radians(light_directional->angles.x), glm::vec3(-1.0f, 0.0f, 0));
		lightModel = glm::rotate(lightModel, glm::radians(light_directional->angles.y), glm::vec3(0.0f, -1.0f, 0));
		lightModel = glm::rotate(lightModel, glm::radians(light_directional->angles.z), glm::vec3(0.0f, 0, -1.0f));
		glm::mat4 lightView = glm::lookAt(light_directional->position - glm::vec3(5, 0, 0), glm::vec3(0),
		                                  glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 lightProjection = orthgonalProjection * lightView * lightModel;
		//把顶点转向灯光视角的矩阵传给simpleDepthShader，用来获取深度图
		simpleDepthShader->use();
		simpleDepthShader->PassMat4ToShader("lightProjection", lightProjection);
		simpleDepthShader->PassMat4ToShader("model", modelMat);
		//把顶点转向灯光视角的矩阵传给sceneShader，用来计算片元在灯光视角下的坐标。
		sceneShader->use();
		sceneShader->PassMat4ToShader("lightSpaceMatrix", lightProjection);
		changeShader->use();
		changeShader->PassMat4ToShader("lightSpaceMatrix", lightProjection);
		standardShader->use();
		standardShader->PassMat4ToShader("lightSpaceMatrix", lightProjection);
		debugDepth->use();
		debugDepth->PassUniformToShader("depthMap", 0);

		simpleDepthShader->use();
		//把视口改成深度图需要的分辨率，准备开始画深度图
		glViewport(0, 0, shadowMapWidth, shadowMapHeight);
		//把shadowMapFBO绑到当前的Framebuffer并激活;
		glBindFramebuffer(GL_FRAMEBUFFER, *shadowMapFBO);
		//这里还要写一个clear，这个问题研究了两天
		//把之前的深度信息清掉
		glClear(GL_DEPTH_BUFFER_BIT);
		//用simpleDepthShader画出场景
		CerberusGun.Draw(simpleDepthShader);

		////model.Draw(simpleDepthShader);
		//simpleDepthShader->PassMat4ToShader("model", sceneModelMat);
		//用simpleDepthShader画出场景
		testScene.Draw(simpleDepthShader);
		bricks.Draw(simpleDepthShader);
		
		//解绑Framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		// 6.shadowMap画完了，把视口尺寸还原到屏幕的尺寸（从shadowmap的尺寸）
		glViewport(0, 0, ScreenWidth, ScreenHeight);
		// 7.把colorbuffer和depthbuffer都清掉，因为shadowmap已经存在shadowMapFBO中的shadowmap上了
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//shadow end
		// ---------------------------------


		if (fboFlag)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, postprocessingFbo);
		}

		// 8.把我们需要显示的场景画出来
		// ---------------------------------*Draw*---------------------------------
		if (showNormal)
		{
			normalVisualizeShader->use();
			normalVisualizeShader->PassMat4ToShader("model", modelMat);
			normalVisualizeShader->PassMat4ToShader("view", view);
			normalVisualizeShader->PassMat4ToShader("projection", projection);
			sphere.Draw(normalVisualizeShader);
		}

		standardShader->use();
		standardShader->PassUniformToShader("ao", ao);

		standardShader->PassMat4ToShader("view", view);
		standardShader->PassMat4ToShader("projection", projection);
		standardShader->PassUniformToShader("camPos", camera.Position);

		standardShader->PassMat4ToShader("model", modelMat);
		standardShader->PassUniformToShader("lightDir", light_directional->direction);
		standardShader->PassUniformToShader("lightPos", light_directional->position);
		standardShader->PassUniformToShader("lightColor", light_directional->color);
		standardShader->PassUniformToShader("lightIntensity", light_directional->intensity);
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, *shadowMap);

		//sphere.Draw(standardShader);
		bricks.Draw(standardShader);
		testScene.Draw(standardShader);
		//Mesh::renderCube();


		modelMat = glm::translate(modelMat, glm::vec3(10.0f, 0,0));
		standardShader->PassMat4ToShader("model", modelMat);
		glActiveTexture(GL_TEXTURE9);
		glBindTexture(GL_TEXTURE_2D, *shadowMap);

		CerberusGun.Draw(standardShader);


		//sceneShader->use();
		////激活第五个texture槽位，给shadowMap，相应的在激活的这个shader里，要把5传到这个shader的shadermap上
		////	sceneShader->PassUniformToShader("shadowMap", 5)，在渲染循环外这样传，这里卡了很久，原来是忘了传
		//glActiveTexture(GL_TEXTURE5);
		//glBindTexture(GL_TEXTURE_2D, *shadowMap);
		//sceneShader->PassMat4ToShader("model", sceneModelMat);
		//testScene.Draw(standardShader);
		standardShader->use();
		//standardShader->PassMat4ToShader("model", sceneModelMat);


		////DEBUG这是把HDR贴图显示在一个方盒子上
		//equalRectTOCubeShader->use();
		//equalRectTOCubeShader->PassMat4ToShader("view", view);
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, hdrTexture);
		//renderCube();



		//drawSkyBos
		skyBox.draw(skyBoxShader, camera, projection, *cubemapFromHDR);

		//把拿到的亮部的buffer做一个高斯模糊
		//---------------------------------*Gaussian*---------------------------------
		bool horizontal = true, first_iteration = true;
		if (fboFlag)
		{
			unsigned int amount = 64;
			gaussianBlurShader->use();
			for (unsigned int i = 0; i < amount; i++)
			{
				glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
				gaussianBlurShader->PassUniformToShader("horizontal", horizontal);
				//第一次迭代的时候先把上面渲出来的高光贴图塞进去做模糊
				if (first_iteration)
				{
					glBindTexture(GL_TEXTURE_2D, bloomColorBuffer);
					first_iteration = false;
				}
				else
				{
					glBindTexture(GL_TEXTURE_2D, pingpongColorBuffers[!horizontal]);
				}
				//每次模糊完都要把图片画出来，画完之后再把当前画的图片塞进去
				glBindVertexArray(quadVAO);
				glDisable(GL_DEPTH_TEST);
				glDrawArrays(GL_TRIANGLES, 0, 6);

				horizontal = !horizontal;
			}
		}

		// 9.把之前的fbo这个framebuffer画在一个平面上。
		//---------------------------------*postProcess*---------------------------------
		if (fboFlag)
		{
			//frameBuffer.draw(screenShader);
			//绑回0，然后画一个framebuffer中 texture的平面
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
			glDisable(GL_DEPTH_TEST);
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			// set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
			glClear(GL_COLOR_BUFFER_BIT);
			glBindVertexArray(quadVAO);
			HdrShader->use();
			HdrShader->PassUniformToShader("exposure", exposure);
			//glBindTexture(GL_TEXTURE_2D, bloomTexture);	// use the color attachment texture as the texture of the quad plane
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, postrocessingColorBuffer);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, pingpongColorBuffers[!horizontal]);
			// use the color attachment texture as the texture of the quad plane
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		//std::cout << glfwGetTime()<<std::endl;
		//glm::vec2 iResolution = glm::vec2(ScreenWidth,ScreenHeight);
		//Aurora->use();
		//Aurora->PassUniformToShader("time", (float)glfwGetTime());
		//Aurora->PassUniformToShader("iResolution", iResolution);
		// 10.这里是debug用的，把之前画在shadowMapFBO中的shadowMap画在一个平面上
		if (shadowMapFlag)
		{
			glViewport(0, 0, 512, 512);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			debugDepth->use();
			glBindVertexArray(quadVAO);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, *shadowMap);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}


		// ---------------------------------*ImGUI*---------------------------------
		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());



		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}


		//CHECK AND CALL EVENT AND SWAP THE BUFFERS	
		//获取用户输入,如果没有这行，就不能获取输入信息，检测那一行就失效了。
		glfwPollEvents();
		//交换double buff 里的缓存内容,没有这行窗口就是一个空白的窗口
		glfwSwapBuffers(window);

		//更新相机位置
		camera.UpdateCameraPos();
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	//结束之后释放内存
	    glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	float offsetX, offsetY;
	offsetX = xPos - lastX;
	offsetY = yPos - lastY;

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(offsetX, offsetY);
}

//读取用户输入并且行动的函数
void processInput(GLFWwindow* window)
{
	float slowSpeed = 0.1f;
	float fastSpeed = 10.0f * slowSpeed;
	float moveSpeed = 1.0f;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}


	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		moveSpeed = fastSpeed;
	}
	else
	{
		moveSpeed = slowSpeed;
	}

	//前后移动
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.SpeedZ = 1.0f * moveSpeed;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.SpeedZ = -1.0f * moveSpeed;
	}
	else
	{
		camera.SpeedZ = 0;
	}
	//左右移动
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.SpeedX = 1.0f * moveSpeed;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.SpeedX = -1.0f * moveSpeed;
	}
	else
	{
		camera.SpeedX = 0;
	}
	//上下移动
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		camera.SpeedY = 1.0f * moveSpeed;
	}
	else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		camera.SpeedY = -1.0f * moveSpeed;
	}
	else
	{
		camera.SpeedY = 0;
	}
	//隐藏鼠标
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}