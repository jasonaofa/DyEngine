#pragma once

#include <glm/glm.hpp>

#include "Shader.h"
#include <assimp/material.h>

namespace DyEngine
{

	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	struct meshTexture
	{
		unsigned int id;
		std::string type;
		std::string path;
	};

	class Mesh
	{
	public:
		static Ref<Mesh> Create(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<meshTexture> textures);

		virtual ~Mesh() = default;
		virtual void Draw(Ref<Shader> shader) = 0;
		virtual void drawCube() = 0;
		virtual void drawQuad() = 0;

	private:
		virtual void setupMesh() = 0;
		//virtual std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) = 0;
	};

}
