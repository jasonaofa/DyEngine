#include "Shader.h"
#include <iostream>
#include <GL/glew.h>
#define GLEW_STATIC
#include  <GLFW/glfw3.h>
#include "fstream"
#include "sstream"
#include <glm.hpp>

Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
	// ---------------------------------*导入文档到OpenGL流程*---------------------------------
	//DISK—>FileBuffer—>StringBuffer(fileStream)—>stringStream—>string—>c string（OpenGL

	// -----------------------------*DISK—>FileBuffer—>StringBuffer(fileStream)*------------------------------
	//InputFileStream = ifstream
	//ifstream vertex 和 fragment file
	//这是创建的filestream(stringBuffer)
	std::ifstream vertexFile;
	std::ifstream fragmentFile;
	std::ifstream geometryFile;

	//Disk—>stringBuffer
	//用filesteam去读filebuffer
	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);

	//检测是否开成功
	try
	{
		// -----------------------------*stringBuffer—>stringStream*------------------------------
		//创建stringStream
		std::stringstream vertexSStream;
		std::stringstream fragmentSStream;
		//vertexFile这时已经打开了vertexPath中的目录，把文件的缓冲内容，导入到数据流中
		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();

		// -----------------------------*stringStream—>string*------------------------------
		//此时vertexSStream中的内容还是 vertexFile刚打开的txt的filestream，我们要转换成string
		//定义在.h中
		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();
		// -----------------------------*string—>c string*------------------------------
		//从string转成c string
		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();
		// -----------------------------*转换成功*------------------------------

		//std::cout << "vertexShaderLoadSuccess" << std::endl;
		//std::cout << "fragmentShaderLoadSuccess" << std::endl;


		//如果文档无法打开failbit，或文档损坏badbit都会抛异常
		vertexFile.exceptions(std::ifstream::badbit || std::ifstream::failbit);
		fragmentFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
		// -----------------------------*GeometryShader*------------------------------
		if (geometryPath != nullptr)
		{
			geometryFile.open(geometryPath);
			std::stringstream geometrySStream;
			geometrySStream << geometryFile.rdbuf();
			geometryString = geometrySStream.str();
			geometrySource = geometryString.c_str();
		}

		if (!vertexFile.is_open() || !fragmentFile.is_open())
		{
			throw std::exception("open file error");
		}
		// -----------------------------*把shader转二进制code*------------------------------
		unsigned int vertex, fragment, geometry;

		//glCreateShader-申请shader用的，这里申请了一个vertexShader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		//把自己写的vertexshader在之前存入到vertexSource之后，再用glShaderSource转换成array。
		glShaderSource(vertex, 1, &vertexSource, NULL);
		//编译
		glCompileShader(vertex);
		checkShaderCompileError(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		checkShaderCompileError(fragment, "FRAGMENT");
		if(geometryPath !=nullptr)
		{
			geometry = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry, 1, &geometrySource, NULL);
			glCompileShader(geometry);
			checkShaderCompileError(geometry, "GEOMETRY");
		}
		//创建shaderprogram
		ID = glCreateProgram();
		//把顶点和片元都attach到ID上
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		if(geometryPath!=nullptr)
		{
			glAttachShader(ID, geometry);
		}
		//此时已经把两个shader的二进制代码绑到program上了，但是他们相互不知道对方的函数位置在哪
		//在链接的时候，两个二进制代码才会紧密的结合在一起，可以完全知道对方的函数地址在哪。
		glLinkProgram(ID);
		checkShaderCompileError(ID, "PROGRAM");
		//删除shader，此时shader都已经在program里了
		glDeleteShader(vertex);
		glDeleteShader(fragment);

		//之后需要用glUseProgram函数use这个programID，opengl才知道用这个program
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

//use new program
void Shader::use()
{
	glUseProgram(ID);
}

//检查shader编译错误的方法
void Shader::checkShaderCompileError(unsigned ID, std::string type)
{
	int success;
	char inforLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ID, 1024, NULL, inforLog);
			std::cout << "shader compile error:" << inforLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 1024, NULL, inforLog);
			std::cout << "program compile error" << inforLog << std::endl;
		}
	}
}

//在初始化material的时候就已经绑过ID值了
void Shader::PassUniformToShader(const char* paramNameString, glm::vec3 param)
{
	glUniform3f(glGetUniformLocation(ID, paramNameString), param.x, param.y, param.z);
}
void Shader::PassUniformToShader(const char* paramNameString, glm::vec2 param)
{
	glUniform2f(glGetUniformLocation(ID, paramNameString), param.x, param.y);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) 
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::PassUniformToShader(const char* paramNameString, float param)
{
	glUniform1f(glGetUniformLocation(ID, paramNameString), param);
}

void Shader::PassUniformToShader(const char* paramNameString, int slot)
{
	glUniform1i(glGetUniformLocation(ID, paramNameString), slot);
}
void Shader::PassUniformToShader(const char* paramNameString, unsigned int slot)
{
	glUniform1i(glGetUniformLocation(ID, paramNameString), slot);
}

void Shader::PassMat4ToShader(const char* paramNameString, glm::mat4 matName)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, paramNameString), 1,GL_FALSE, glm::value_ptr(matName));
}
