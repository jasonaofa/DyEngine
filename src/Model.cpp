#include "Model.h"

#include "Shader.h"
#include "stb_image.h"
#pragma once

Model::Model(std::string path)
{
	loadModel(path);
}
//把mashes画出来
void Model::Draw(Shader* shader)
{
	shader->use();
	for (unsigned int i = 0;i<meshes.size();i++)
	{
		//这里用的是mesh里的draw方法
		meshes[i].Draw(shader);
	}
}


//读路径的
void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	//用aiScene建立根节点scene
	//这里一定要有const
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "Assimp::error::" <<importer.GetErrorString()<< std::endl;
	}
	//这里两个'\\'前面那个\是转义符,两个表示一个真的'\'
	directory = path.substr(0, path.find_last_of('\\'));
	std::cout <<"directory is :"<< directory << std::endl;
	//d:\work\CPP\opengl\abc.exe
	//比如上面这个地址,就可以用substr挖到最后一个'\'为止,得到的就是directory=d:\work\CPP\opengl\'
	std::cout <<"Sucess get this directory:" << directory << std::endl;
	//第一个node（骨骼）取rootnode
	processNode(scene->mRootNode,scene);
}
//递归每一个节点
void Model::processNode(aiNode* node, const aiScene* scene)
{
	////这样就会把所有的子节点名字都打印出来
	//std::cout << node->mName.data<<std::endl;
	//把当前node下的mesh给到我们建立的mesh下面
	// 处理节点所有的网格（如果有的话）
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* curMesh = scene->mMeshes[node->mMeshes[i]];
		//把处理好的模型数据给到meshes，然后用draw函数去把mash画出来
		meshes.push_back(processMesh(curMesh, scene));

	}
	//递归遍历传进来的node下面的所有children
	// 接下来对它的子节点重复这一过程
	for (unsigned int i = 0 ;i<node->mNumChildren;i++)
	{
		processNode(node->mChildren[i],scene);
	}

}
//处理面的函数，处理面的顶点数据，索引数据和问题
Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	//下面三个vector是Mesh类需要的参数，用这三个来构成一个mesh。
	//需要被填充的数据
	std::vector<Vertex> tempVertices;
	std::vector<unsigned int> tempIndices;
	std::vector<Texture>tempTextures;

	glm::vec3 tempVec;

	//遍历顶点，mesh有多少个顶点，就循环多少次，
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		//以下操作就是对mesh中的一个顶点进行

		//————————————把mesh中的顶点填充到我们的tempVertices中————————————
		//建立一个临时顶点
		Vertex temVertex;
		//把顶点的顶点坐标给到临时的temVertex
		temVertex.Position.x = mesh->mVertices[i].x;
		temVertex.Position.y = mesh->mVertices[i].y;
		temVertex.Position.z = mesh->mVertices[i].z;
		//把顶点的法线坐标给到临时的temVertex
		temVertex.Normal.x = mesh->mNormals[i].x;
		temVertex.Normal.y = mesh->mNormals[i].y;
		temVertex.Normal.z = mesh->mNormals[i].z;

		//把顶点的UV坐标给到临时的temVertex，如果没有uv，就给他（0，0）；
		//第0组uvmap，一般是模型。uv1一般是光影烘焙
		if (mesh->mTextureCoords[0])
		{
			temVertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
			temVertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			temVertex.TexCoords = glm::vec2(0, 0);
		}
		//顶点的三个信息都处理完了，把已经存了信息的temVertex顶点，pushback给我们的tempVertices
		tempVertices.push_back(temVertex);
	}
	//assimp定义了每个网格都有一个面（face）数字，每个面代表了一个图元，在我们的例子中（由于使用了aiProcess_Triangulate选项）它总是三角形
	//遍历face的面
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		//遍历当前面的索引数量
		for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
		{
			//把i个面的j索引，pushback给我们的tempIndices
			tempIndices.push_back(mesh->mFaces[i].mIndices[j]);
		}
	}
	//处理材质
	if (mesh->mMaterialIndex >= 0)
	{
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	//diffuse maps
	std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_albedo");
	tempTextures.insert(tempTextures.end(), diffuseMaps.begin(), diffuseMaps.end());
	////specular maps
	std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_metallic");
	tempTextures.insert(tempTextures.end(), specularMaps.begin(), specularMaps.end());
	//normal maps
	std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	tempTextures.insert(tempTextures.end(), normalMaps.begin(), normalMaps.end());
	//	//normal maps
	//std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	//tempTextures.insert(tempTextures.end(), normalMaps.begin(), normalMaps.end());
	////height maps
	//std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	//tempTextures.insert(tempTextures.end(), heightMaps.begin(), heightMaps.end());
	//reflect maps
	std::vector<Texture> reflectionMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_roughness");
	tempTextures.insert(tempTextures.end(), reflectionMaps.begin(), reflectionMaps.end());
	std::vector<Texture> aoMaps = loadMaterialTextures(material, aiTextureType_EMISSIVE, "texture_ao");
	tempTextures.insert(tempTextures.end(), aoMaps.begin(), aoMaps.end());
	}
	//把我们从模型路径里拿出来的顶点信息，索引信息和贴图信息，返还给我们创造的Mesh类
	return Mesh(tempVertices, tempIndices, tempTextures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// 用来判断只加载一次的flag
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				//加载过之后就把纹理的flag变成true，这样没有被加载过的就是false
				skip = true; 
				break;
			}
		}
		if (!skip)
		{   
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), this->directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture);  
		}
	}
	return textures;
}


//把纹理的文件从路径中读进来
unsigned int Model::TextureFromFile(const char* path, const std::string& directory, bool gamma)
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
		GLenum format,hdrFormat;
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
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}



