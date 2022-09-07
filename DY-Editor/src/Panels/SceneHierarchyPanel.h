#pragma once

#include "DyEngine/Core/Base.h"
#include "DyEngine/Core/Log.h"
#include "DyEngine/Scene/Scene.h"
#include "DyEngine/Scene/Entity.h"

namespace DyEngine {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender();


		Entity GetSelectedEntity() const { return m_SelectionContext; }
	private:
		void DrawComponents(Entity entity);
		void DrawEntityNode(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};

}
