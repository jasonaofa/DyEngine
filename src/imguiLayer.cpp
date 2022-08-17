#include "imguiLayer.h"



 void imguiLayer::begin()
{
	// Poll and handle events (inputs, window resize, etc.)
	glfwPollEvents();
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	//void BeginFrame();//Start the gizmo
	ImGui::NewFrame();
}

 //void imguiLayer::setUp(GLFWwindow* window, ImGuiIO& io)
 //{
	// // Setup Dear ImGui context
	// IMGUI_CHECKVERSION();
	// ImGui::CreateContext();
	// (void)io;
	// io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	// io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	// io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows


	// // Setup Dear ImGui style
	// ImGui::StyleColorsDark();

	// // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	// ImGuiStyle& style = ImGui::GetStyle();
	// if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	// {
	//	 style.WindowRounding = 0.0f;
	//	 style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	// }

	// // Setup Platform/Renderer backends
	// ImGui_ImplGlfw_InitForOpenGL(window, true);
	// ImGui_ImplOpenGL3_Init("#version 330");
 //}

 //void imguiLayer::renderer(ImGuiIO& io)
 //{        // Rendering
	// ImGui::Render();
	// ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	// (void)io;

	// // Update and Render additional Platform Windows
	// // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	// //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
	// if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	// {
	//	 GLFWwindow* backup_current_context = glfwGetCurrentContext();
	//	 ImGui::UpdatePlatformWindows();
	//	 ImGui::RenderPlatformWindowsDefault();
	//	 glfwMakeContextCurrent(backup_current_context);
	// }
 //}
