#pragma once

#include "DyEngine.h"

class Sandbox2D : public DyEngine::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(DyEngine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(DyEngine::Event& e) override;
private:
	DyEngine::OrthographicCameraController m_CameraController;

	// Temp
	DyEngine::Ref<DyEngine::VertexArray> m_SquareVA;
	DyEngine::Ref<DyEngine::Shader> m_FlatColorShader;

	DyEngine::Ref<DyEngine::Texture2D> m_CheckerboardTexture;

	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;


	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};