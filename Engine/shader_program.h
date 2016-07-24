#ifndef ENGINE_SHADER_PROGRAM_H
#define ENGINE_SHADER_PROGRAM_H
#include <string>
#include <vector>
#include <memory>
#include "GL/glew.h"

class Shader;
class Matrix4;
//class containing an opengl shader program and associated information
class ShaderProgram : public std::enable_shared_from_this<ShaderProgram>
{
	std::string viewPositionUniform;
	GLuint programID;
	bool isValid = false;
public:
	ShaderProgram();
	void AttachShader(const Shader& shader);
	bool BindAsActiveProgram();
	void SetUniform(std::string uniformName, const Matrix4& value);
};
#endif