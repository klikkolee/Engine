#include "shader_program.h"
#include "shader.h"
#include "matrix4.h"

ShaderProgram::ShaderProgram()
{
	programID = glCreateProgram();
	glLinkProgram(programID);

	GLint result = GL_FALSE;
	GLint infoLogLength = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> perrorMessage(infoLogLength + 1);
	glGetProgramInfoLog(programID, infoLogLength, nullptr, &perrorMessage[0]);
	isValid = result;
}

void ShaderProgram::AttachShader(const Shader & shader)
{
	glAttachShader(programID, shader.shaderID);
	glLinkProgram(programID);

	GLint result = GL_FALSE;
	GLint infoLogLength = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> perrorMessage(infoLogLength + 1);
	glGetProgramInfoLog(programID, infoLogLength, nullptr, &perrorMessage[0]);
	isValid = result;
}

bool ShaderProgram::BindAsActiveProgram()
{
	if (isValid)
	{
		glUseProgram(programID);
		return true;
	}
	else
		return false;
}

void ShaderProgram::SetUniform(std::string uniformName, const Matrix4 & value)
{
	float buffer[16] = {};
	value.AsFloatBuffer(buffer);
	GLuint uniform = glGetUniformLocation(programID, uniformName.c_str());
	glUniformMatrix4fv(uniform, 1, GL_TRUE, buffer);
}
