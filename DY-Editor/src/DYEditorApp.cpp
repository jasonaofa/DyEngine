#include <DyEngine.h>
#include <DyEngine/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace DyEngine {

	class DYEditor : public Application
	{
	public:
		DYEditor(): Application("DY Editor")
		{
			PushLayer(new EditorLayer());
		}

		~DYEditor()
		{
		}
	};

	Application* CreateApplication()
	{
		return new DYEditor();
	}

}