#ifndef ENGINE_SHADER_H
#define ENGINE_SHADER_H
#include <string>
#include <memory>
#include "GL/glew.h"

//class containing individual opengl shaders
class Shader : public std::enable_shared_from_this<Shader>
{
public:
	friend class ShaderProgram;
	enum ShaderType
	{
		VERTEX_SHADER = GL_VERTEX_SHADER,
		FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
		GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
		TESSELATION_CONTROL_SHADER = GL_TESS_CONTROL_SHADER,
		TESSELATION_EVALUATION_SHADER = GL_TESS_EVALUATION_SHADER,
		COMPUTE_SHADER = GL_COMPUTE_SHADER,
		UNDEFINED_SHADER = -1
	};
	Shader(ShaderType = UNDEFINED_SHADER);
	Shader(ShaderType, std::string);
private:
	ShaderType type = UNDEFINED_SHADER;
	bool isValid = false;
	GLuint shaderID;
};

#endif
