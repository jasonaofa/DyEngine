#pragma once
#include "OpenGLMesh.h"
#include "assimp/scene.h"

#include "DyEngine/Renderer/Model.h"


namespace DyEngine
{
	class OpenGLModel :public Model
	{
	public:
		OpenGLModel(std::string path);
		void Draw(Ref<Shader> shader) override ;

		void loadModel(std::string path);
		void processNode(aiNode* node, const aiScene* scene);

		glm::vec3 angles = glm::vec3(0, 0, 0);
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 translate = glm::vec3(0, 0, 0);
		std::vector<OpenGLMesh> meshes;
		std::string directory;
		std::vector<meshTexture> textures_loaded;

		unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);
		OpenGLMesh processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<meshTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	};
}
