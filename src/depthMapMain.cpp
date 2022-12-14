//#define GLEW_STATIC
////load images
//#define STB_IMAGE_IMPLEMENTATION
//#include <filesystem>
//#include <iostream>
//#include "stb_image.h"
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include "Shader.h"
//#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
//#include <gtc/type_ptr.hpp>
//#include "fstream"
//#include "sstream"
//#include "imgui.h"
//#include "imgui/imgui_impl_glfw.h"
//#include "imgui/imgui_impl_opengl3.h"
//#include "Camera.h"
//#include "FrameBuffer.h"
//#include "Material.h"
//#include "LightDirectional.h"
//#include "LightPoint.h"
//#include "LightSpot.h"
//#include "Mesh.h"
//#include "Model.h"
//#include "SkyBox.h"
////#include "imguiLayer.h"
//
//class LightSpot;
//
////loadt texture function
//unsigned int loadCubmap(const std::vector<std::string>& faces)
//{
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
//
//	int width, height, nrChannels;
//	for (unsigned int i = 0; i < faces.size(); i++)
//	{
//		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
//		//翻转Y轴，GL和stbimage这个库的Y轴是反的
//		stbi_set_flip_vertically_on_load(true);
//
//		if (data)
//		{
//			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
//			             0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
//			);
//			stbi_image_free(data);
//		}
//		else
//		{
//			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
//			stbi_image_free(data);
//		}
//	}
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//
//
//	return textureID;
//}
//
//
///**
// * \brief 把图片读到GPU的方法，返回的是图片在VAO上的槽位ID
// * \param imageName 图片的名称
// * \param internalFormat 
// * \param format 
// * \param textureSlotNumber texture的槽位，从0开始
// * \return 
// */
//unsigned int LoadImageToGPU(const char* imageName, GLint internalFormat, GLenum format, int textureSlotNumber)
//{
//	//第一个TextureBuffeR
//	unsigned int textureBuffer;
//	glGenTextures(1, &textureBuffer);
//	//绑定到TEXTURE_2D的0号槽，并激活
//	glActiveTexture(GL_TEXTURE0 + textureSlotNumber);
//	//把texturebuffer绑到VAO的TEXTURE_2D这个位置
//	glBindTexture(GL_TEXTURE_2D, textureBuffer);
//
//	int width, height, nrChannels;
//	unsigned char* imageData = stbi_load(imageName, &width, &height, &nrChannels, 0);
//	//翻转Y轴，GL和stbimage这个库的Y轴是反的
//	stbi_set_flip_vertically_on_load(false);
//	if (imageData)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);
//		glGenerateMipmap(GL_TEXTURE_2D);
//		//std::cout << imageData << std::endl;
//	}
//	else
//	{
//		std::cout << "load image1 failed." << std::endl;
//	}
//	stbi_image_free(imageData);
//	return textureBuffer;
//}
//
//// ---------------------------------*imGUI*---------------------------------
////imguiLayer im_Gui;
//
//#pragma region Camera&Input
//// ---------------------------------*相机*---------------------------------
////Camera camera(glm::vec3(0, 10.0f, 30.0f), glm::radians(0.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::radians(0.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));
//
//// ---------------------------------*鼠标*---------------------------------
////上一次鼠标的x和y坐标
//float lastX = 960;
//float lastY = 540;
//bool firstMouse = true;
//
//void mouse_callback(GLFWwindow* window, double xPos, double yPos)
//{
//	if (firstMouse)
//	{
//		lastX = xPos;
//		lastY = yPos;
//		firstMouse = false;
//	}
//	float offsetX, offsetY;
//	offsetX = xPos - lastX;
//	offsetY = yPos - lastY;
//
//	lastX = xPos;
//	lastY = yPos;
//
//	camera.ProcessMouseMovement(offsetX, offsetY);
//}
//
//void mouseNotCallback(GLFWwindow* window, double xPos, double yPos)
//{
//}
//
////读取用户输入并且行动的函数
//void processInput(GLFWwindow* window)
//{
//	float moveSpeed = 1.0f;
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(window, true);
//	}
//
//	if (glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
//	{
//		if (glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
//		{
//			moveSpeed = 10.0f;
//		}
//		else
//		{
//			moveSpeed = 1.0f;
//		}
//
//		//前后移动
//		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		{
//			camera.SpeedZ = 1.0f * moveSpeed;
//		}
//		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		{
//			camera.SpeedZ = -1.0f * moveSpeed;
//		}
//		else
//		{
//			camera.SpeedZ = 0;
//		}
//		//左右移动
//		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		{
//			camera.SpeedX = 1.0f * moveSpeed;
//		}
//		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		{
//			camera.SpeedX = -1.0f * moveSpeed;
//		}
//		else
//		{
//			camera.SpeedX = 0;
//		}
//		//上下移动
//		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
//		{
//			camera.SpeedY = 1.0f * moveSpeed;
//		}
//		else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
//		{
//			camera.SpeedY = -1.0f * moveSpeed;
//		}
//		else
//		{
//			camera.SpeedY = 0;
//		}
//
//
//		// ---------------------------------*鼠标*---------------------------------
//		//关闭鼠标
//		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//	}
//	else
//	{
//		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//	}
//}
//#pragma endregion
//
//
//
//
//
//unsigned int planeVBO, planeVAO;
//void renderScene(Shader* shader);
//void renderQuad();
//
//
//
//
//
//
//
//
//
//// #################################*MAIN*######################################
//int main(int argc, char* argv[])
//{
//	//argv[0]代表的就是第生产的EXE,他的路径是C:\Users\frank\Documents\GitHub\LearnOpenGL\MyOpenGL\Debug\MyOpenGL.exe
//	std::string exePath = argv[0];
//	//此时会得到C:\Users\frank\Documents\GitHub\LearnOpenGL\MyOpenGL\Debug
//	std::cout << exePath.substr(0, exePath.find_last_of('\\')) << std::endl;
//	//路径是可以加的,此时得到C:\Users\frank\Documents\GitHub\LearnOpenGL\MyOpenGL\Debug\modelnanosuit.obj
//	std::cout << exePath.substr(0, exePath.find_last_of('\\')) + "\\" + "model" + "nanosuit.obj" << std::endl;
//#pragma region Open Window & Set mouse
//	//初始化
//	glfwInit();
//	//主版本号3
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	//副版本号3，所以版本是3.3
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	//用core_profile
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	//创建一个window指针变量
//	GLFWwindow* window = glfwCreateWindow(1920, 1080, "MyOpenGL", nullptr, nullptr);
//	if (window == nullptr)
//	{
//		std::cout << "打开窗口失败" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	//Initial GLEW
//	glewExperimental = true;
//	if (glewInit() != GLEW_OK)
//	{
//		std::cout << "Initial GLEW failed" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	//创建一个视窗
//	float ScreenWidth = 1920;
//	float ScreenHeight = 1080;
//	glViewport(0, 0, ScreenWidth, ScreenHeight);
//	//Z_BUFFER
//	glEnable(GL_DEPTH_TEST);
//	///Cull
//	glEnable(GL_CULL_FACE);
//	//gamma
//	glEnable(GL_FRAMEBUFFER_SRGB);
//#pragma endregion
//#pragma region Init Shader Program
//	// ---------------------------------*Shader*---------------------------------
//	Shader* myShader = new Shader("vertexShader.glsl", "fragmentShader.glsl");
//	Shader* screenShader = new Shader("screenVertexShader.glsl", "screenFragmentShader.glsl");
//	Shader* skyBoxShader = new Shader("skyBoxVertexShader.glsl", "skyBoxFragmentShader.glsl");
//	Shader* normalVisualizeShader = new Shader("NVisualizeVertex.glsl", "NVisualizeFragment.glsl",
//	                                           "NVisualizeGeometry.glsl");
//	Shader* simpleDepthShader = new Shader("simpleDepthShaderVS.glsl", "simpleDepthFRAG.glsl");
//	Shader* debugDepth = new Shader("debugDepthVS.glsl", "debugDepthFRAG.glsl");
//#pragma endregion
//	// ---------------------------------*Material*---------------------------------
//	//这里先初始化一下，在render循环里再给想要的值
//	Material* material = new Material(myShader,
//	                                  //ambient
//	                                  glm::vec3(0.3f, 0.3f, 0.f),
//	                                  //diffuse
//	                                  LoadImageToGPU("1", GL_RGB, GL_RGBA, Shader::DIFFUSE),
//	                                  //specular
//	                                  LoadImageToGPU("1", GL_RGB, GL_RGBA, Shader::SPECULAR),
//	                                  //emission
//	                                  LoadImageToGPU("1", GL_RGB, GL_RGB, Shader::EMISSION),
//	                                  //reflection
//	                                  LoadImageToGPU("1", GL_RGB, GL_RGB, Shader::Reflection),
//	                                  //specular power value
//	                                  32.0f);
//	//---------------------------------*SkyBox*---------------------------------
//	SkyBox skyBox;
//	skyBox.set(skyBoxShader, myShader);
//
//	std::vector<std::string> faces
//	{
//		"resources/textures/skyBox_right.png",
//		"resources/textures/skyBox_left.png",
//		"resources/textures/skyBox_up.png",
//		"resources/textures/skyBox_down.png",
//		"resources/textures/skyBox_front.png",
//		"resources/textures/skyBox_back.png",
//	};
//	unsigned int cubmapTexture = loadCubmap(faces);
//
//	////---------------------------------*Framebuffer*---------------------------------
//	//FrameBuffer frameBuffer;
//	//frameBuffer.setQuad();
//
//#pragma region Light Declare
//	// ---------------------------------*Light*---------------------------------
//	LightDirectional* light_directional = new LightDirectional(
//		//position
//		glm::vec3(1.0f, 1.0f, 1.0f),
//		//angle
//		glm::vec3(180.0f, 0.0f, 0.0f),
//		//color
//		glm::vec3(1.0f, 1.0f, 1.0f),
//		//intensity
//		float(1.0f)
//	);
//
//	LightPoint* light_point0 = new LightPoint(
//		glm::vec3(1.0f, 0, 0),
//		glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
//		glm::vec3(1.0f, 0, 0)
//	);
//	LightPoint* light_point1 = new LightPoint(
//		glm::vec3(0, 1.0f, 0),
//		glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
//		glm::vec3(0, 1.0f, 0)
//	);
//	LightPoint* light_point2 = new LightPoint(
//		glm::vec3(0, 0, 1.0f),
//		glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
//		glm::vec3(0, 0, 1.0f)
//	);
//	LightPoint* light_point3 = new LightPoint(
//		glm::vec3(1.0f, 1.0f, 1.0f),
//		glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
//		glm::vec3(1.0f, 1.0f, -1.0f)
//	);
//	LightSpot* light_spot = new LightSpot(
//		glm::vec3(0, 30.0f, 0),
//		glm::vec3(glm::radians(90.0f), 0, 0),
//		glm::vec3(1.0f, 1.0f, 1.0f)
//	);
//#pragma endregion
//
//	Model model(exePath.substr(0, exePath.find_last_of('\\')) + "\\" + "Models" + "\\" + "nanosuit.obj");
//	Model testScene(exePath.substr(0, exePath.find_last_of('\\')) + "\\" + "Models" + "\\" + "cz" + "\\" + "all.obj");
//
//	// ---------------------------------*ImGUI*---------------------------------
//	// Setup Dear ImGui context
//	IMGUI_CHECKVERSION();
//	ImGui::CreateContext();
//	ImGuiIO& io = ImGui::GetIO();
//	(void)io;
//	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
//	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
//	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
//
//	// Setup Dear ImGui style
//	ImGui::StyleColorsDark();
//
//	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
//	ImGuiStyle& style = ImGui::GetStyle();
//	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
//	{
//		style.WindowRounding = 0.0f;
//		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
//	}
//
//	// Setup Platform/Renderer backends
//	ImGui_ImplGlfw_InitForOpenGL(window, true);
//	ImGui_ImplOpenGL3_Init("#version 330");
//	// Our state
//	bool show_demo_window = true;
//	bool show_another_window = false;
//
//	// ---------------------------------*ShadowMap*---------------------------------
//	//生成并绑定FBO
//	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
//	unsigned int depthMapFBO;
//	glGenFramebuffers(1, &depthMapFBO);
//	//生成纹理附件
//	unsigned int depthMap;
//	glGenTextures(1, &depthMap);
//	glBindTexture(GL_TEXTURE_2D, depthMap);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
//	             NULL);
//	//设置参数
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//	//use our depthMap replace framebuffer's depthMap in renderbuffer
//	//
//	glBindFramebuffer(GL_FRAMEBUFFER, depthMap);
//	//接下来，作为完成帧缓冲之前的最后一步，我们将渲染缓冲对象附加到帧缓冲的深度和模板附件上：
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
//	//set the texturebuffer(颜色缓冲) to none,for the integrity of framebuffer
//	//glDrawBuffer(GL_NONE);
//	//glReadBuffer(GL_NONE);
//	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
//		std::cout << "Framebuffer is  complete!" << std::endl;
//	//解绑
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//	debugDepth->use();
//	debugDepth->PassUniformToShader("depthMap", 0);
//
//	glm::vec4 orthgraphicProjection = glm::ortho(-35.0f, 35.0f, -35.0f, 35.0f,0.1f,75.0f);
//	//// ---------------------------------*FrameBuffer*---------------------------------
//	////后处理用的
//	////TODO 完成阴影之后再来把后处理处理好
//	//frameBuffer.setFbo(ScreenWidth, ScreenHeight);
//	// ---------------------------------*Flags*---------------------------------
//	bool mouseFlag = false;
//	static int clicked = 0;
//	static int fboClicked = 0;
//	static int showNormalClicked = 0;
//	bool fboFlag = false;
//	bool showNormal = false;
//
//
//
//
//
//
//
//
//
//
//
//
//	float planeVertices[] = {
//		// positions            // normals         // texcoords
//		 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
//		-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
//		-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
//
//		 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
//		-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
//		 25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
//	};
//	// plane VAO
//	glGenVertexArrays(1, &planeVAO);
//	glGenBuffers(1, &planeVBO);
//	glBindVertexArray(planeVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//	glBindVertexArray(0);
//
//
//	// lighting info
//// -------------
//	glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//	// #################################*渲染循环*######################################
//	while (!glfwWindowShouldClose(window))
//	{
//#pragma region IMGUI
//		//---------------------------------*ImGUI*---------------------------------
//		// Poll and handle events (inputs, window resize, etc.)
//		glfwPollEvents();
//		// Start the Dear ImGui frame
//		ImGui_ImplOpenGL3_NewFrame();
//		ImGui_ImplGlfw_NewFrame();
//		ImGui::NewFrame();
//		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
//		if (show_demo_window)
//			ImGui::ShowDemoWindow(&show_demo_window);
//		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
//		{
//			ImGui::Begin("inspector"); // Create a window called "Hello, world!" and append into it.
//			ImGui::Text("My Owen Render Demo v0.0.1");
//
//			if (ImGui::Button("LineMode"))
//				clicked++;
//			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//			if (clicked & 1)
//			{
//				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//			}
//
//			if (ImGui::Button("Blur"))
//				fboClicked++;
//			fboFlag = false;
//			if (fboClicked & 1)
//			{
//				fboFlag = true;
//			}
//
//			if (ImGui::Button("showNormal"))
//				showNormalClicked++;
//			showNormal = false;
//			if (showNormalClicked & 1)
//			{
//				showNormal = true;
//			}
//
//			ImGui::Checkbox("Another Window", &show_another_window);
//
//			ImGui::Text("DirLight:");
//			ImGui::SliderFloat("DirLight Intensity", &light_directional->intensity, 0.0f, 5.0f);
//			// Edit 1 float using a slider from 0.0f to 1.0f
//			ImGui::ColorEdit3("DirLigh Ccolor", (float*)&light_directional->color);
//			// Edit 3 floats representing a color
//			ImGui::SliderFloat3("LightDirection", (float*)&light_directional->angles, -360, 360);
//			ImGui::Spacing();
//
//			ImGui::Text("Model:");
//			ImGui::SliderFloat3("ModelRotation", (float*)&model.angles, -360.0f, 360.0f);
//			ImGui::SliderFloat("ModelScale", (float*)&model.scale, 0, 10.0f);
//			ImGui::Text("Scene:");
//			ImGui::InputFloat3("SceneRotation", (float*)&testScene.angles);
//			ImGui::SliderFloat("SceneScale", (float*)&testScene.scale, 0, 10.0f);
//			ImGui::InputFloat3("SceneTranslate", (float*)&testScene.translate);
//
//			//这里记得要更新direction，因为们是传direction到shader，而angles的值在初始化的时候就定了，然后马上会调用这个函数去更新方向，
//			//所以如果不在这里再次更新方向，那angles的值就算用指针变了，但是他不会更新成direction。
//			light_directional->UpdateDirection();
//
//
//			ImGui::Text("Application average (%.0f FPS)", ImGui::GetIO().Framerate);
//			ImGui::End();
//		}
//
//		// 3. Show another simple window.
//		if (show_another_window)
//		{
//			ImGui::Begin("Another Window", &show_another_window);
//			// Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
//			ImGui::Text("Hello from another window!");
//			if (ImGui::Button("Close Me"))
//				show_another_window = false;
//			ImGui::End();
//		}
//#pragma endregion
//
//
//		//INPUT HERE
//		//检测用户输入的信息并进行操作
//		processInput(window);
//		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
//		{
//			//注册回调函数
//			//一旦鼠标移动，就会检测到x和y给值给mouse_callback
//			glfwSetCursorPosCallback(window, mouse_callback);
//			bool firstMouse = true;
//		}
//		////TODO 修改这一行，让鼠标在不按右键的时候不会控制摄像机镜头
//		////这行会和GUI冲突，先注释掉
//		//else glfwSetCursorPosCallback(window, NULL);	
//
//
//		// render
//		// ------
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//
//		//// ---------------------------------*MVP矩阵*---------------------------------
//		////声明
//		//glm::mat4 view, projection, modelMat;
//		////赋值
//		//modelMat = glm::rotate(modelMat, glm::radians(model.angles.x), glm::vec3(1.0f, 0.0f, 0));
//		//modelMat = glm::rotate(modelMat, glm::radians(model.angles.y), glm::vec3(0.0f, 1.0f, 0));
//		//modelMat = glm::rotate(modelMat, glm::radians(model.angles.z), glm::vec3(0.0f, 0, -1.0f));
//		//modelMat = glm::scale(modelMat, glm::vec3(model.scale.x, model.scale.x, model.scale.x));
//		//view = camera.GetViewMatrix();
//		//projection = glm::perspective(glm::radians(45.0f), ScreenWidth / ScreenHeight, 0.1f, 100.0f);
//
//
//		//myShader->use(); //这里要记得切到主shader，记住opengl是个状态机
//		//myShader->PassMat4ToShader("model", modelMat);
//		//myShader->PassMat4ToShader("view", view);
//		//myShader->PassMat4ToShader("projection", projection);
//		//// ---------------------------------*材质*---------------------------------
//		////DIRECTIONAL LIGHT
//		//myShader->PassUniformToShader("lightD.pos", light_directional->position);
//		//myShader->PassUniformToShader("lightD.color", light_directional->color);
//		//myShader->PassUniformToShader("lightD.dirToLight", light_directional->direction);
//		//myShader->PassUniformToShader("lightD.intensity", light_directional->intensity);
//		////POINT LIGHT
//		//myShader->PassUniformToShader("lightP0.pos", light_point0->position);
//		//myShader->PassUniformToShader("lightP0.color", light_point0->color);
//		//myShader->PassUniformToShader("lightP0.dirToLight", light_point0->lightDir);
//		//myShader->PassUniformToShader("lightP0.constant", light_point0->constant);
//		//myShader->PassUniformToShader("lightP0.linear", light_point0->linear);
//		//myShader->PassUniformToShader("lightP0.quadratic", light_point0->quadratic);
//		////SPOT LIGHT
//		//myShader->PassUniformToShader("spotLight.cosPhiInner", light_spot->cosPhiInner);
//		//myShader->PassUniformToShader("spotLight.cosPhiOuter", light_spot->cosPhiOuter);
//		//myShader->PassUniformToShader("spotLight.pos", light_spot->position);
//		//myShader->PassUniformToShader("spotLight.color", light_spot->color);
//		//myShader->PassUniformToShader("spotLight.dirToLight", light_spot->direction);
//		//myShader->PassUniformToShader("spotLight.constant", light_spot->constant);
//		//myShader->PassUniformToShader("spotLight.linear", light_spot->linear);
//		//myShader->PassUniformToShader("spotLight.quadratic", light_spot->quadratic);
//		////CAMERA
//		//myShader->PassUniformToShader("cameraPos", camera.Position);
//		////material
//		//myShader->PassUniformToShader("material.ambient", material->ambient);
//		//myShader->PassUniformToShader("material.specular", Shader::SPECULAR);
//		//myShader->PassUniformToShader("material.diffuse", Shader::DIFFUSE);
//		//myShader->PassUniformToShader("material.emission", Shader::EMISSION);
//		//myShader->PassUniformToShader("material.reflection", Shader::Reflection);
//		//myShader->PassUniformToShader("material.shininess", material->shininess);
//
//		//// ---------------------------------*framebuffer*---------------------------------
//		////postProcessing
//		////bind to framebuffer
//		//if (fboFlag)
//		//{
//		//	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer.fbo);
//		//}
//		//glEnable(GL_DEPTH_TEST);
//		//glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
//		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		// 1. render depth of scene to texture (from light's perspective)
//		// --------------------------------------------------------------
//		// ---------------------------------*ShadowMap*---------------------------------
//		glm::mat4 lightProjection, lightView, lightSpaceMatrix;
//		float near_plane = 1.0f, far_plane = 7.5f;
//		lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
//		lightView = glm::lookAt(light_directional->position, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//		lightSpaceMatrix = lightProjection * lightView;
//		//从灯光视角渲染场景
//		simpleDepthShader->use();
//		simpleDepthShader->PassMat4ToShader("lightSpaceMatrix", lightSpaceMatrix);
//		//设置视口的长款,因为shadowmap的尺寸和视窗的尺寸是不一样的
//		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
//		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
//		glClear(GL_DEPTH_BUFFER_BIT);
//		//draw all of the scene
//		//// ---------------------------------*DrawAtShadowMap*---------------------------------
//		////TODO 把深度采样的渲染部分写好，用simpleDepthShader去渲染场景中需要计算投影的物体生成深度贴图
//		////https://learnopengl.com/code_viewer_gh.php?code=src/5.advanced_lighting/3.1.2.shadow_mapping_base/shadow_mapping_base.cpp
//		////drawModel
//		//simpleDepthShader->PassMat4ToShader("model", modelMat);
//		//model.Draw(simpleDepthShader);
//
//		//testScene.translate = glm::vec3(130.0f, -23.0f, 500.0f);
//		//testScene.scale = glm::vec3(3.0f, 3.0f, 3.0f);
//		//modelMat = glm::scale(modelMat, testScene.scale);
//		//modelMat = glm::translate(modelMat, testScene.translate);
//		//simpleDepthShader->PassMat4ToShader("model", modelMat);
//		//testScene.Draw(simpleDepthShader);
//		renderScene(simpleDepthShader);
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//		// reset viewport
//		glViewport(0, 0, ScreenWidth, ScreenHeight);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//
//		//// 2. render scene as normal using the generated depth/shadow map  
//		//// ---------------------------------*Draw*---------------------------------
//		////drawModel
//		//model.Draw(myShader);
//		//if (showNormal)
//		//{
//		//	normalVisualizeShader->use();
//		//	normalVisualizeShader->PassMat4ToShader("model", modelMat);
//		//	normalVisualizeShader->PassMat4ToShader("view", view);
//		//	normalVisualizeShader->PassMat4ToShader("projection", projection);
//		//	model.Draw(normalVisualizeShader);
//		//}
//		//myShader->use();
//		//testScene.translate = glm::vec3(130.0f,-23.0f,500.0f);
//		//testScene.scale = glm::vec3(3.0f,3.0f,3.0f);
//		//modelMat = glm::scale(modelMat, testScene.scale);
//		//modelMat = glm::translate(modelMat,testScene.translate);
//		//myShader->PassMat4ToShader("model", modelMat);
//		//testScene.Draw(myShader);
//
//
//		////drawSkyBos
//		//skyBox.draw(skyBoxShader, camera, projection, cubmapTexture);
//		//////postProcess
//		////if (fboFlag)
//		////{
//		////	frameBuffer.draw(screenShader);
//		////}
//
//		//3. render Depth map to quad for visual debugging
//		// ---------------------------------------------
//		debugDepth->use();
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, depthMap);
//
//		renderQuad();
//
//		glBindVertexArray(0);
//
//		// ---------------------------------*ImGUI*---------------------------------
//		// Rendering
//		ImGui::Render();
//		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//
//
//		// Update and Render additional Platform Windows
//		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
//		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
//		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
//		{
//			GLFWwindow* backup_current_context = glfwGetCurrentContext();
//			ImGui::UpdatePlatformWindows();
//			ImGui::RenderPlatformWindowsDefault();
//			glfwMakeContextCurrent(backup_current_context);
//		}
//
//
//		//CHECK AND CALL EVENT AND SWAP THE BUFFERS	
//		//获取用户输入,如果没有这行，就不能获取输入信息，检测那一行就失效了。
//		glfwPollEvents();
//		//交换double buff 里的缓存内容,没有这行窗口就是一个空白的窗口
//		glfwSwapBuffers(window);
//
//		//更新相机位置
//		camera.UpdateCameraPos();
//	}
//
//	// Cleanup
//	ImGui_ImplOpenGL3_Shutdown();
//	ImGui_ImplGlfw_Shutdown();
//	ImGui::DestroyContext();
//
//	//结束之后释放内存
//	glfwTerminate();
//	return 0;
//}
//
//
//// -------------------------------------------------
//unsigned int cubeVAO = 0;
//unsigned int cubeVBO = 0;
//
//void renderCube()
//{
//	// initialize (if necessary)
//	if (cubeVAO == 0)
//	{
//		float vertices[] = {
//			// back face
//			-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
//			1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // top-right
//			1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
//			1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // top-right
//			-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
//			-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, // top-left
//			// front face
//			-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
//			1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // bottom-right
//			1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top-right
//			1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top-right
//			-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // top-left
//			-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
//			// left face
//			-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
//			-1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-left
//			-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
//			-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
//			-1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-right
//			-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
//			// right face
//			1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-left
//			1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
//			1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right         
//			1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
//			1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-left
//			1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-left     
//			// bottom face
//			-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
//			1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, // top-left
//			1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom-left
//			1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom-left
//			-1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom-right
//			-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
//			// top face
//			-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top-left
//			1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
//			1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top-right     
//			1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
//			-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top-left
//			-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f // bottom-left        
//		};
//		glGenVertexArrays(1, &cubeVAO);
//		glGenBuffers(1, &cubeVBO);
//		// fill buffer
//		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//		// link vertex attributes
//		glBindVertexArray(cubeVAO);
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//		glEnableVertexAttribArray(1);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//		glEnableVertexAttribArray(2);
//		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		glBindVertexArray(0);
//	}
//	// render Cube
//	glBindVertexArray(cubeVAO);
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//	glBindVertexArray(0);
//}
//
//void renderCube();
//
//void renderScene(Shader* shader)
//{
//	// floor
//	glm::mat4 model = glm::mat4(1.0f);
//	shader->PassMat4ToShader("model", model);
//	glBindVertexArray(planeVAO);
//	glDrawArrays(GL_TRIANGLES, 0, 6);
//	// cubes
//	model = glm::mat4(1.0f);
//	model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
//	model = glm::scale(model, glm::vec3(0.5f));
//	shader->PassMat4ToShader("model", model);
//	renderCube();
//	model = glm::mat4(1.0f);
//	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
//	model = glm::scale(model, glm::vec3(0.5f));
//	shader->PassMat4ToShader("model", model);
//	renderCube();
//	model = glm::mat4(1.0f);
//	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
//	model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
//	model = glm::scale(model, glm::vec3(0.25));
//	shader->PassMat4ToShader("model", model);
//	renderCube();
//}
//
//unsigned int quadVAO = 0;
//unsigned int quadVBO;
//void renderQuad()
//{
//	if (quadVAO == 0)
//	{
//		float quadVertices[] = {
//			// positions        // texture Coords
//			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
//			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
//			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
//			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
//		};
//		// setup plane VAO
//		glGenVertexArrays(1, &quadVAO);
//		glGenBuffers(1, &quadVBO);
//		glBindVertexArray(quadVAO);
//		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//		glEnableVertexAttribArray(1);
//		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	}
//	glBindVertexArray(quadVAO);
//	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//	glBindVertexArray(0);
//}