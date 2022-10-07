#include "Shaders.h"
#include <fstream>

namespace {

	std::stringstream createString(std::filesystem::path file) {
		auto absolute = std::filesystem::absolute(file);
		auto stream = std::ifstream(absolute.c_str());
		std::stringstream buffer;
		buffer << stream.rdbuf();
		return buffer;
	}
}

void Shaders::compileShaders(const std::vector<std::pair<GLuint*, std::string>>& uniforms) {

	{
		m_shaderProgram = glCreateProgram();

		if (!m_shaderProgram)
		{
			printf("Failed to create shader\n");
			return;
		}

		auto vertexShader = createString(m_vertexShader);
		auto fragmentShader = createString(m_fragShader);


		addShader(m_shaderProgram, vertexShader.str().c_str(), GL_VERTEX_SHADER);
		addShader(m_shaderProgram, fragmentShader.str().c_str(), GL_FRAGMENT_SHADER);

		GLint result = 0;
		GLchar eLog[1024] = { 0 };

		glLinkProgram(m_shaderProgram);
		glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &result);
		if (!result)
		{
			glGetProgramInfoLog(m_shaderProgram, sizeof(eLog), NULL, eLog);
			printf("Error linking program: '%s'\n", eLog);
			return;
		}

		glValidateProgram(m_shaderProgram);
		glGetProgramiv(m_shaderProgram, GL_VALIDATE_STATUS, &result);
		if (!result)
		{
			glGetProgramInfoLog(m_shaderProgram, sizeof(eLog), NULL, eLog);
			printf("Error validating program: '%s'\n", eLog);
			return;
		}

		for (auto& uniform : uniforms) {
			*(uniform.first) = glGetUniformLocation(m_shaderProgram, uniform.second.c_str());
		}
	}

}

const GLuint Shaders::getShaderProgram()
{
	return m_shaderProgram;
}

void Shaders::addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);
	const GLchar* code = shaderCode;
	const GLchar* const* pcode = &code;
	const GLint codeSize = strlen(shaderCode);

	glShaderSource(theShader, 1, &shaderCode, &codeSize);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, 1024, NULL, eLog);
		fprintf(stderr, "Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}
