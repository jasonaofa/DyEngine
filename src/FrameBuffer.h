#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"


class FrameBuffer
{
public:
	unsigned int quadVAO,quadVBO, fbo,rbo, texColorBuffer;
	void setQuad();
	void setFbo(GLsizei width, GLsizei height);
	void draw(Shader* screenShader);
};

