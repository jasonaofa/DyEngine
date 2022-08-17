#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"
class imguiLayer
{
public:
	ImGuiIO& io = ImGui::GetIO();
	void begin();
	//void setUp(GLFWwindow* window, ImGuiIO& io);
	//void renderer(ImGuiIO& io);
};

