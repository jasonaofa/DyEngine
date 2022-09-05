#pragma once

#include "DyEngine.h"

class ExampleLayer : public DyEngine::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(DyEngine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(DyEngine::Event& e) override;
private:
	DyEngine::ShaderLibrary m_ShaderLibrary;
	DyEngine::Ref<DyEngine::Shader> m_Shader;
	DyEngine::Ref<DyEngine::VertexArray> m_VertexArray;

	DyEngine::Ref<DyEngine::Shader> m_FlatColorShader;
	DyEngine::Ref<DyEngine::VertexArray> m_SquareVA;

	DyEngine::Ref<DyEngine::Texture2D> m_Texture, m_ChernoLogoTexture;

	DyEngine::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};
