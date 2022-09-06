#pragma once

//只给sandbox的application用的，这样就不用在sanboxApp.cpp文件中写一堆包含了

#include "DyEngine/Core/Base.h"
#include "DyEngine/Core/Timestep.h"

#include "DyEngine/Core/Application.h"
#include "DyEngine/Core/Log.h"
#include "DyEngine/ImGui/ImGuiLayer.h"

#include "DyEngine/Core/Input.h"
#include "DyEngine/Core/KeyCodes.h"
#include "DyEngine/Core/MouseButtonCodes.h"
#include "DyEngine/Core/Layer.h"


//---------Scene-----------
#include "DyEngine/Scene/Scene.h"
#include "DyEngine/Scene/Components.h"
//---------Render-----------
#include "DyEngine/Renderer/Renderer2D.h"
#include "DyEngine/Renderer/Renderer.h"
#include "DyEngine/Renderer/RenderCommand.h"

#include "DyEngine/Renderer/Buffer.h"
#include "DyEngine/Renderer/Shader.h"
#include "DyEngine/Renderer/Framebuffer.h"
#include "DyEngine/Renderer/VertexArray.h"
#include "DyEngine/Renderer/Texture.h"
#include "DyEngine/Renderer/OrthographicCameraController.h"

#include "DyEngine/Renderer/OrthographicCamera.h"
//-------------------------------
 