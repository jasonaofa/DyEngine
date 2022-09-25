#pragma once

#include <glm/glm.hpp>
#include <assimp/material.h>

namespace DyEngine
{
	class Shader;

	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	struct Texture
	{
		unsigned int id;
		std::string type;
		std::string path;
	};

	class Mesh
	{
	public:
		static Ref<Mesh> Create(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

		virtual ~Mesh() = default;
		virtual void Draw(Shader* shader) = 0;

	private:
		virtual void setupMesh() = 0;
		virtual std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) = 0;
	};

}
