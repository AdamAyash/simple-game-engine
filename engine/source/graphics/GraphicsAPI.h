#pragma once

#include <GL/glew.h>
#include <memory>
#include <string>

class ShaderProgram;

namespace engine
{
	class GraphicsAPI
	{
	public:
		std::shared_ptr<ShaderProgram> CreateShaderProgram(const std::string& vertexSource,
			const std::string fragmentSource);
	};
}