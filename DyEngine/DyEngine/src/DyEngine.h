#pragma once

//只给sandbox的application用的，这样就不用在sanboxApp.cpp文件中写一堆包含了
#include <iostream>

#include "DyEngine/Core/Timestep.h"

#include "DyEngine/Core.h"
#include "DyEngine/Application.h"
#include "DyEngine/Log.h"
#include "DyEngine/ImGui/ImGuiLayer.h"
#include "DyEngine/Input.h"
#include "DyEngine/Core/KeyCodes.h"
#include "DyEngine/Core/MouseButtonCodes.h"
#include "DyEngine/Layer.h"
//---------Render-----------
#include "DyEngine/Renderer/Renderer.h"
#include "DyEngine/Renderer/RenderCommand.h"

#include "DyEngine/Renderer/Buffer.h"
#include "DyEngine/Renderer/Shader.h"
#include "DyEngine/Renderer/VertexArray.h"

#include "DyEngine/Renderer/OrthographicCamera.h"
//-------------------------------

//---------Entry Point-----------
#include "DyEngine/EntryPoint.h"
//-------------------------------