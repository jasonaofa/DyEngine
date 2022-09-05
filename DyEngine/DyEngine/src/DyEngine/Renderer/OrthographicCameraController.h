#pragma once

#include "DyEngine/Renderer/OrthographicCamera.h"
#include "DyEngine/Core/Timestep.h"

#include "DyEngine/Events/ApplicationEvent.h"
#include "DyEngine/Events/MouseEvent.h"

namespace DyEngine {

	class OrthographicCameraController
	{
	public:
		/**
		 * \brief 
		 * \param aspectRatio 横纵比
		 * \param rotation 
		 */
		OrthographicCameraController(float aspectRatio, bool rotation = true);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;//In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};

}