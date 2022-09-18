#pragma once

#include "DyEngine.h"
#include "Panels/SceneHierarchyPanel.h"
#include "DyEngine/Renderer/EditorCamera.h"
namespace DyEngine {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;

	public:
		Entity m_Test_01;

	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);

		void NewScene();
		void OpenScene();
		void SaveSceneAs();
	private:
		DyEngine::OrthographicCameraController m_CameraController;

		// Temp
		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;
		Ref<Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;

		Entity m_HoveredEntity;



		bool m_PrimaryCamera = true;

		Ref<Texture2D> m_CheckerboardTexture;
		EditorCamera m_EditorCamera;
		bool m_ViewportFocused = true, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBounds[2];
		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
		//Gizmo
		int m_GizmoType = -1;


		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
	};

}