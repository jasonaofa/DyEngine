#pragma once

#include "DyEngine.h"
#include "Panels/SceneHierarchyPanel.h"
#include "DyEngine/Renderer/EditorCamera.h"
#include "DyEngine/Renderer/Environment.h"
#include "DyEngine/Renderer/Model.h"


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
		//Environment::EnvData& env_data ;
		Ref<Environment> m_Environment ;

		// Temp
		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;
		Ref<Shader> m_FlatColorShader_2;
		Ref<Shader> env_cloudsShader;
		Ref<Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_TownEntity;
		Entity env_Entity;

		Entity m_CameraEntity;
		Entity m_SecondCamera;
		Entity m_HoveredEntity;



		bool m_PrimaryCamera = true;

		Ref<Model> m_Scene;
		Ref<Texture2D> m_CheckerboardTexture;
		EditorCamera m_EditorCamera;
		bool m_ViewportFocused = true, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBounds[2];
		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
		//Gizmo
		int m_GizmoType = -1;


		Environment::CloudsStats cloudStatsDefault;
		Environment::CloudsStats cloudStats_01 ;
		Environment::CloudsStats cloudStats_02;
		Environment::CloudsStats cloudStats_03 ;
		Environment::SunStats sunStats;

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
	};

}
