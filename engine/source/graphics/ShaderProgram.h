#pragma once

#include <GL/glew.h>
#include <string>
#include <unordered_map>

namespace engine
{
	class ShaderProgram
	{
	public:
		ShaderProgram() = delete;
		ShaderProgram(const ShaderProgram& shaderProgram) = delete;
		ShaderProgram& operator = (const ShaderProgram& shaderProgram) = delete;

		explicit ShaderProgram(GLuint shaderProgramId);
		~ShaderProgram();

	public:
		void Bind();
		const GLint GetUniformLocation(const std::string& name);
		void SetUniform(const std::string& name, float value);

	private:
		GLuint m_shaderProgramId;
		std::unordered_map<std::string, GLuint> m_uniformLocationCache;
	};
}
