#include "Material.h"
#include <glm.hpp>
#include <iostream>
#include <ostream>

#include "Shader.h"
#include "stb_image.h"

//Material::Material(Shader* _shader, glm::vec3 _ambient, unsigned int _diffuse, unsigned int _specular,unsigned int _emission,unsigned _reflection, float _shininess):
//shader(_shader),ambient(_ambient),diffuse(_diffuse),specular(_specular), emission(_emission),reflection(_reflection), shininess(_shininess)
//{
//}
Material::Material(Shader* _shader, unsigned int _albedo, unsigned int _metallic, unsigned int _normal, unsigned int _roughness, unsigned int _ao) :
	shader(_shader), albedo(_albedo), metallic(_metallic), normal(_normal), roughness(_roughness), ao(_ao)
{
}

 unsigned int Material::LoadImageToGPU(const char* imageName)
{
	int width, height, nrChannels;
	//判断一下通道数。自动选择格式
	GLenum format;


	//第一个TextureBuffeR
	unsigned int textureBuffer;
	glGenTextures(1, &textureBuffer);

	//把texturebuffer绑到VAO的TEXTURE_2D这个位置
	glBindTexture(GL_TEXTURE_2D, textureBuffer);


	unsigned char* imageData = stbi_load(imageName, &width, &height, &nrChannels, 0);
	if (nrChannels == 1)
		format = GL_RED;
	else if (nrChannels == 3)
		format = GL_RGB;
	else if (nrChannels == 4)
		format = GL_RGBA;

	//翻转Y轴，GL和stbimage这个库的Y轴是反的
	stbi_set_flip_vertically_on_load(false);
	if (imageData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
		//std::cout << imageData << std::endl;
	}
	else
	{
		std::cout << "load image1 to GPUI failed." << std::endl;
	}
	stbi_image_free(imageData);
	return textureBuffer;
}