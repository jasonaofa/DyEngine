#include "DyPch.h"
#include "OpenGLModel.h"
#include "glad/glad.h"
#include <imgui_impl_opengl3_loader.h>
#include <assimp/Importer.hpp>

#include "postprocess.h"
#include "scene.h"
#include "stb_image.h"


namespace DyEngine
{
	OpenGLModel::OpenGLModel(std::string path)
	{
		loadModel(path);
	}
	//��mashes������
	void OpenGLModel::Draw(Ref<Shader> shader)
	{
		shader->Bind();
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			//�����õ���mesh���draw����
			meshes[i].Draw(shader);
		}
	}
	//��·����
	void OpenGLModel::loadModel(std::string path)
	{
		Assimp::Importer importer;
		//��aiScene�������ڵ�scene
		//����һ��Ҫ��const
		const aiScene* scene = importer.ReadFile(
			path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "Assimp::error::" << importer.GetErrorString() << std::endl;
		}
		directory = path.substr(0, path.find_last_of('/'));
		
		//std::cout <<"directory is :"<< directory << std::endl;
		//d:\work\CPP\opengl\abc.exe
		//�������������ַ,�Ϳ�����substr�ڵ����һ��'\'Ϊֹ,�õ��ľ���directory=d:\work\CPP\opengl\'
		//std::cout <<"Sucess get this directory:" << directory << std::endl;
		//��һ��node��������ȡrootnode
		processNode(scene->mRootNode, scene);
	}

	//�ݹ�ÿһ���ڵ�
	void OpenGLModel::processNode(aiNode* node, const aiScene* scene)
	{
		////�����ͻ�����е��ӽڵ����ֶ���ӡ����
		//std::cout << node->mName.data<<std::endl;
		//�ѵ�ǰnode�µ�mesh�������ǽ�����mesh����
		// ����ڵ����е���������еĻ���
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* curMesh = scene->mMeshes[node->mMeshes[i]];
			//�Ѵ���õ�ģ�����ݸ���meshes��Ȼ����draw����ȥ��mash������
			meshes.push_back(processMesh(curMesh, scene));
		}
		//�ݹ������������node���������children
		// �������������ӽڵ��ظ���һ����
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}

	//������ĺ�����������Ķ������ݣ��������ݺ�����
	OpenGLMesh OpenGLModel::processMesh(aiMesh* mesh, const aiScene* scene)
	{
		//��������vector��Mesh����Ҫ�Ĳ�������������������һ��mesh��
		//��Ҫ����������
		std::vector<Vertex> tempVertices;
		std::vector<unsigned int> tempIndices;
		std::vector<meshTexture>tempTextures;

		glm::vec3 tempVec;

		//�������㣬mesh�ж��ٸ����㣬��ѭ�����ٴΣ�
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			//���²������Ƕ�mesh�е�һ���������

			//��������������������������mesh�еĶ�����䵽���ǵ�tempVertices�С�����������������������
			//����һ����ʱ����
			Vertex temVertex;
			//�Ѷ���Ķ������������ʱ��temVertex
			temVertex.Position.x = mesh->mVertices[i].x;
			temVertex.Position.y = mesh->mVertices[i].y;
			temVertex.Position.z = mesh->mVertices[i].z;
			//�Ѷ���ķ������������ʱ��temVertex
			temVertex.Normal.x = mesh->mNormals[i].x;
			temVertex.Normal.y = mesh->mNormals[i].y;
			temVertex.Normal.z = mesh->mNormals[i].z;

			//�Ѷ����UV���������ʱ��temVertex�����û��uv���͸�����0��0����
			//��0��uvmap��һ����ģ�͡�uv1һ���ǹ�Ӱ�決
			if (mesh->mTextureCoords[0])
			{
				temVertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
				temVertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
			}
			else
			{
				temVertex.TexCoords = glm::vec2(0, 0);
			}
			//�����������Ϣ���������ˣ����Ѿ�������Ϣ��temVertex���㣬pushback�����ǵ�tempVertices
			tempVertices.push_back(temVertex);
		}
		//assimp������ÿ��������һ���棨face�����֣�ÿ���������һ��ͼԪ�������ǵ������У�����ʹ����aiProcess_Triangulateѡ�������������
		//����face����
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			//������ǰ�����������
			for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
			{
				//��i�����j������pushback�����ǵ�tempIndices
				tempIndices.push_back(mesh->mFaces[i].mIndices[j]);
			}
		}
		//�������
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			//diffuse maps
			std::vector<meshTexture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_albedo");
			tempTextures.insert(tempTextures.end(), diffuseMaps.begin(), diffuseMaps.end());
			////specular maps
			std::vector<meshTexture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_metallic");
			tempTextures.insert(tempTextures.end(), specularMaps.begin(), specularMaps.end());
			//normal maps

			std::vector<meshTexture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
			tempTextures.insert(tempTextures.end(), normalMaps.begin(), normalMaps.end());
			//	//normal maps
			//std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
			//tempTextures.insert(tempTextures.end(), normalMaps.begin(), normalMaps.end());
			////height maps
			//std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
			//tempTextures.insert(tempTextures.end(), heightMaps.begin(), heightMaps.end());
			//reflect maps
			std::vector<meshTexture> reflectionMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_roughness");
			tempTextures.insert(tempTextures.end(), reflectionMaps.begin(), reflectionMaps.end());
			std::vector<meshTexture> aoMaps = loadMaterialTextures(material, aiTextureType_EMISSIVE, "texture_ao");
			tempTextures.insert(tempTextures.end(), aoMaps.begin(), aoMaps.end());
		}
		//�����Ǵ�ģ��·�����ó����Ķ�����Ϣ��������Ϣ����ͼ��Ϣ�����������Ǵ����Mesh��
		return OpenGLMesh(tempVertices, tempIndices, tempTextures);
	}

	std::vector<meshTexture> OpenGLModel::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
	{
		std::vector<meshTexture> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			bool skip = false;
			for (unsigned int j = 0; j < textures_loaded.size(); j++)
			{
				if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
				{
					textures.push_back(textures_loaded[j]);
					//���ع�֮��Ͱ������flag���true������û�б����ع��ľ���false
					skip = true;
					break;
				}
			}
			if (!skip)
			{
				meshTexture texture;
				texture.id = TextureFromFile(str.C_Str(), this->directory);
				texture.type = typeName;
				texture.path = str.C_Str();
				textures.push_back(texture);
				textures_loaded.push_back(texture);
			}
		}
		return textures;
	}
	//��������ļ���·���ж�����
	unsigned int OpenGLModel::TextureFromFile(const char* path, const std::string& directory, bool gamma)
	{
		std::string filename = std::string(path);
		filename = directory + '/' + filename;

		unsigned int textureID;
		glGenTextures(1, &textureID);

		int width, height, nrComponents;
		unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
		stbi_set_flip_vertically_on_load(false);
		if (data)
		{
			GLenum format, hdrFormat;
			if (nrComponents == 1)
			{
				format = GL_RED;
				hdrFormat = GL_RED;
			}
			else if (nrComponents == 3)
			{
				format = GL_RGB;
				hdrFormat = GL_RGB16F;
			}
			else if (nrComponents == 4)
			{
				format = GL_RGBA;
				hdrFormat = GL_RGBA16F;
			}


			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, hdrFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else
		{
			std::cout << "Texture failed to load at path: " << filename << std::endl;
			stbi_image_free(data);
		}

		return textureID;
	}






}
