#include "Core.h"
#include "stb_image.h"

GLuint captureFBO;
GLuint captureRBO;

void Core::getShdowFboMap(GLuint* shadowMapFBO, GLuint* shadowMap, GLsizei shadowMapWidth, GLsizei shadowMapHeight)
{

	glGenFramebuffers(1, &*shadowMapFBO);
	//生成纹理附件
	glGenTextures(1, &*shadowMap);
	glBindTexture(GL_TEXTURE_2D, *shadowMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT,
		GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	// Prevents darkness outside the frustrum
	float clampColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clampColor);

	glBindFramebuffer(GL_FRAMEBUFFER, *shadowMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, *shadowMap, 0);
	// Needed since we don't touch the color buffer
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
};

GLuint Core::getQuadVAO()
{
	float quadVertices[] = {
		// positions   // texCoords
		-1.0f, 1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 0.0f,

		-1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	};
	unsigned int quadVAO, quadVBO;
	// screen quad VAO
	glGenVertexArrays(1, &quadVAO);
	glBindVertexArray(quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	return quadVAO;
};






void Core::getIndirectDiffuseMaps(GLuint* cubemapFromHDR, GLuint* irradianceMap, Shader* equalRectTOCubeShader, Shader* irradianceMapShader)
{

	glGenFramebuffers(1, &captureFBO);
	glGenRenderbuffers(1, &captureRBO);

	glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
	glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 2048, 2048);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO);


	stbi_set_flip_vertically_on_load(true);
	int width, height, nrComponents;
	float* data = stbi_loadf(HDRPath, &width, &height, &nrComponents, 0);
	unsigned int hdrTexture;
	if (data)
	{
		glGenTextures(1, &hdrTexture);
		glBindTexture(GL_TEXTURE_2D, hdrTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data);
		// note how we specify the texture's data value to be float

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Failed to load HDR image." << std::endl;
	}

	// pbr: setup cubemap to render to and attach to framebuffer
	// ---------------------------------------------------------

	glGenTextures(1, &*cubemapFromHDR);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *cubemapFromHDR);
	for (unsigned int i = 0; i < 6; ++i)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 2048, 2048, 0, GL_RGB, GL_FLOAT, nullptr);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// pbr: convert HDR equirectangular environment map to cubemap equivalent
	// ----------------------------------------------------------------------
	equalRectTOCubeShader->use();
	equalRectTOCubeShader->PassUniformToShader("equirectangularMap", 0);
	equalRectTOCubeShader->PassMat4ToShader("projection", captureProjection);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, hdrTexture);

	glViewport(0, 0, 2048, 2048); // don't forget to configure the viewport to the capture dimensions.
	glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
	for (unsigned int i = 0; i < 6; ++i)
	{
		equalRectTOCubeShader->PassMat4ToShader("view", captureViews[i]);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, *cubemapFromHDR, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Mesh::renderCube();
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// then let OpenGL generate mipmaps from first mip face (combatting visible dots artifact)
	glBindTexture(GL_TEXTURE_CUBE_MAP, *cubemapFromHDR);
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	// pbr: create an irradiance cubemap, and re-scale capture FBO to irradiance scale.
	// --------------------------------------------------------------------------------

	glGenTextures(1, &*irradianceMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *irradianceMap);
	for (unsigned int i = 0; i < 6; ++i)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 32, 32, 0, GL_RGB, GL_FLOAT, nullptr);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
	glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 32, 32);


	// pbr: solve diffuse integral by convolution to create an irradiance (cube)map.
	// -----------------------------------------------------------------------------
	irradianceMapShader->use();
	irradianceMapShader->PassUniformToShader("environmentMap", 0);
	irradianceMapShader->PassMat4ToShader("projection", captureProjection);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *cubemapFromHDR);

	glViewport(0, 0, 32, 32); // don't forget to configure the viewport to the capture dimensions.
	glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
	for (unsigned int i = 0; i < 6; ++i)
	{
		irradianceMapShader->PassMat4ToShader("view", captureViews[i]);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, *irradianceMap,
			0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Mesh::renderCube();

	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//---------------------------------*镜面反射部分*---------------------------------
//这里用的是EPIC的split sum approximation（分别求和近似法
//Lo(p, ωo) = ∫Ω Li(p, ωi)dωi∗ ∫Ω fr(p, ωi, ωo)n⋅ωidωi

//预滤波HDR环境贴图-Pre-filtering an HDR environment map
// -------------------------------------------------------------
void Core::getIndirectSpecularMaps(GLuint* prefilterMap, GLuint* brdfLUTTexture, GLuint* cubemapFromHDR,Shader* preFilterShader,Shader* genBrdfLutShader)
{
	glGenTextures(1, &*prefilterMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *prefilterMap);
	for (unsigned int i = 0; i < 6; ++i)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 128, 128, 0, GL_RGB, GL_FLOAT, nullptr);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// be sure to set minification filter to mip_linear 
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//这句让opengl自动去分配Mipmap需要的内存
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	//对环境照明运行一个近似蒙特卡洛积分的模拟，从而创建一个prefilter (cube)map.
	//用preFilterShader 对上面的Pre-filtering an HDR environment map 进行处理
	//得到基于粗糙度来决定PDF函数的，门特卡罗的近似
	//------------------------------------------------------------

	preFilterShader->use();
	preFilterShader->PassUniformToShader("environmentMap", 0);
	preFilterShader->PassMat4ToShader("projection", captureProjection);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *cubemapFromHDR);

	glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
	unsigned int maxMipLevels = 5;
	for (unsigned int mip = 0; mip < maxMipLevels; ++mip)
	{
		unsigned int mipWidth = static_cast<unsigned int>(128 * std::pow(0.5, mip));
		unsigned int mipHeight = static_cast<unsigned int>(128 * std::pow(0.5, mip));
		glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mipWidth, mipHeight);
		glViewport(0, 0, mipWidth, mipHeight);

		float roughness = (float)mip / (float)(maxMipLevels - 1);
		preFilterShader->PassUniformToShader("roughness", roughness);

		for (unsigned int i = 0; i < 6; i++)
		{
			preFilterShader->PassMat4ToShader("view", captureViews[i]);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				*prefilterMap, mip);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			Mesh::renderCube();
		}
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑第一部分处理完毕了，此时已经有了不同MIP等级的prefilter hdr cubemap 了
	//第二部分，就是生成一张LUT图，当然也可以用别人生成好的
	//我们以 BRDF 的输入n⋅ωi（范围在 0.0 和 1.0 之间）作为横坐标，以粗糙度作为纵坐标。
	//------------------------------------------------------------

	glGenTextures(1, &*brdfLUTTexture);

	// pre-allocate enough memory for the LUT texture.
	glBindTexture(GL_TEXTURE_2D, *brdfLUTTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, 512, 512, 0, GL_RG, GL_FLOAT, 0);
	// be sure to set wrapping mode to GL_CLAMP_TO_EDGE
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// then re-configure capture framebuffer object and render screen-space quad with BRDF shader.
	glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
	glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *brdfLUTTexture, 0);

	glViewport(0, 0, 512, 512);
	genBrdfLutShader->use();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Mesh::renderQuad();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
};

