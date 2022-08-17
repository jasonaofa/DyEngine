#pragma once

#include <string>
#include <vector>
#include <GL/glew.h>
#include <iostream>
#include <detail/type_mat.hpp>
#include "Camera.h"



class Camera;
class Shader;

class SkyBox
{
public:
	unsigned int VAO, VBO;
	int width, height, nrChannels;
	Shader* shader ;


	void set(Shader* skyboxShader, Shader* modelShader); 

	void draw(Shader* shader,Camera camera, glm::mat4 projection,unsigned int cubmapTexture);

	unsigned int loadCubmap(const std::vector<std::string>& faces);

	
};

