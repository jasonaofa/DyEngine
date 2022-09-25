#include "DyPch.h"
#include "OpenGLMesh.h"

namespace DyEngine
{
	OpenGLMesh::OpenGLMesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, std::vector<Texture> textures)
		:m_Vertices(vertices), m_Indices(indices), m_Textures(textures)
	{
		//把顶点绑到VAO上
		setupMesh();
	}
	
}
