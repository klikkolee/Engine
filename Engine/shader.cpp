#include "shader.h"
#include "log.h"
#include <fstream>
#include <vector>

Shader::Shader(ShaderType type)
{
	shaderID = glCreateShader(type);
}

Shader::Shader(ShaderType type, std::string file) : Shader(type)
{
	this->type = type;

	std::string shaderCode;
	std::ifstream shaderFileStream(file, std::ios::in);
	if (shaderFileStream.is_open()) {
		std::string Line = "";
		while (getline(shaderFileStream, Line))
			shaderCode += "\n" + Line;
		shaderFileStream.close();
	}
	else {
		Log("unable to open shader from file %s", file.c_str());
		isValid = false;
		return;
	}
	const char* shaderCodeCString = shaderCode.c_str();

	glShaderSource(shaderID, 1, &shaderCodeCString, nullptr);
	glCompileShader(shaderID);

	GLint result = GL_FALSE;
	int infoLogLength;

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> errorMessage(infoLogLength + 1);
	glGetShaderInfoLog(shaderID, infoLogLength, nullptr, &errorMessage[0]);
	if(!result)
		Log(&errorMessage[0]);
	isValid = result;
}
