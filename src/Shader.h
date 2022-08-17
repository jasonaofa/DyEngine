#pragma once
#include <string>
#include <detail/type_vec.hpp>
#include <GL/glew.h>
#include <gtc/type_ptr.hpp>

class Shader
{
public:
	Shader(const char* vertexPath = nullptr, const char* fragmentPath = nullptr, const char* geometryPath = nullptr);
	std::string vertexString;
	std::string fragmentString;
	std::string geometryString;
	const char* vertexSource;
	const char* fragmentSource;
	const char* geometrySource;
	unsigned int ID;//shader program ID
	enum slotNum
	{
		DIFFUSE,
		SPECULAR,
		EMISSION,
		Reflection
	};
	void use();
	void PassUniformToShader(const char* paramNameString, glm::vec3 param);
	void PassUniformToShader(const char* paramNameString, glm::vec2 param);
	void setVec3(const std::string& name, const glm::vec3& value);
	void PassUniformToShader(const char* paramNameString, float param);
	void PassUniformToShader(const char* paramNameString, int slot);
	void PassUniformToShader(const char* paramNameString, unsigned int slot);
	void PassMat4ToShader(const char* paramNameString, glm::mat4 matName);

private:
	void checkShaderCompileError(unsigned int ID, std::string type);
};

	
