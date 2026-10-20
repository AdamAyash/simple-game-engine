#include "graphics/ShaderProgram.h"

namespace engine
{
	ShaderProgram::ShaderProgram(GLuint shaderProgramId)
		: m_shaderProgramId(shaderProgramId)
	{
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_shaderProgramId);
 	}

	void ShaderProgram::Bind()
	{
		glUseProgram(m_shaderProgramId);
	}

	const GLint ShaderProgram::GetUniformLocation(const std::string& name)
	{
		auto it = m_uniformLocationCache.find(name);
		if (it != m_uniformLocationCache.end())
		{
			return it->second;
		}

		GLint location = glGetUniformLocation(m_shaderProgramId, name.c_str());
		m_uniformLocationCache[name] = location;
		return location;
	}

	void ShaderProgram::SetUniform(const std::string& name, float value)
	{
		const auto location = GetUniformLocation(name);
		glUniform1f(location, value);
	}

	void ShaderProgram::SetUniform(const std::string& name, float v0, float v1)
	{
		const auto location = GetUniformLocation(name);
		glUniform2f(location, v0, v1);
	}
}