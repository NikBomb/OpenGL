#ifndef SHADERS_H
#define SHADERS_H
#include <filesystem>
#include <gl/glew.h>

class Shaders {
public:
	Shaders(std::filesystem::path vertexSh, std::filesystem::path fragShader) : m_vertexShader{ std::move(vertexSh) }, m_fragShader{ std::move(fragShader) } {};
	void compileShaders(const std::vector<std::pair<GLuint*, std::string>>& uniforms);
	const GLuint getShaderProgram();
private:
	void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
	std::filesystem::path m_vertexShader;
	std::filesystem::path m_fragShader;
	GLuint m_shaderProgram;
};

#endif