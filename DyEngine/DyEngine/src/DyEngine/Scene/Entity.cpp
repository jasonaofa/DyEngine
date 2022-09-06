#include "DyPch.h"
#include "Entity.h"

namespace DyEngine{

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

}