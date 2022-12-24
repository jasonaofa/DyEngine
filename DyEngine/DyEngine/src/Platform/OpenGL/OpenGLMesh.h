#pragma once
#include "DyEngine/Renderer/Mesh.h"

namespace DyEngine
{

	class OpenGLMesh : public Mesh
	{
	public:
		OpenGLMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		OpenGLMesh();
		void Draw(Shader* shader);
		virtual ~OpenGLMesh();
	private:
		unsigned int m_VAO, m_VBO, m_EBO;
		std::vector<Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;
		std::vector<Texture> m_Textures;
		void setupMesh();
		std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	};
}

