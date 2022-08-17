#pragma once
#include <cstddef>
#include <GL/glew.h>
#include "Mesh.h"
#include "Shader.h"
#include <gtc/matrix_transform.hpp>


class Core
{
public:

	//static Shader* equalRectTOCubeShader;
	//static Shader* irradianceMapShader;
	//static Shader* preFilterShader;
	//static Shader* genBrdfLutShader;


	//functions
	static void getShdowFboMap(GLuint* shadowMapFBO, GLuint* shadowMap, GLsizei shadowMapWidth, GLsizei shadowMapHeight);
	static GLuint getQuadVAO();
	static void getIndirectDiffuseMaps(GLuint* cubemapFromHDR, GLuint* irradianceMap, Shader* equalRectTOCubeShader, Shader* irradianceMapShader);
	static void getIndirectSpecularMaps(GLuint* prefilterMap, GLuint* brdfLUTTexture, GLuint* cubemapFromHDR, Shader* preFilterShader, Shader* genBrdfLutShader);


private:
	
	static inline char const* HDRPath = "resources/textures/hdr/Arches_E_PineTree_3k.hdr";
	static  inline glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 100.0f);
	static  inline glm::mat4 captureViews[] =
	{
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f))
	};




};

