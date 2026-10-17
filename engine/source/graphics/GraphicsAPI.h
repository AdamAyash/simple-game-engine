#pragma once

#include <GL/glew.h>
#include <memory>
#include <string>
#include <iostream>


namespace engine
{
	class ShaderProgram;

	class GraphicsAPI
	{
	public:
		std::shared_ptr<ShaderProgram> CreateShaderProgram(const std::string& vertexSourcePath,
			const std::string& fragmentSourcePath);

		void BindShaderProgram(ShaderProgram* shaderProgram);

    private:
        // utility function for checking shader compilation/linking errors.
        // ------------------------------------------------------------------------
		bool checkCompileErrors(unsigned int shader, std::string type);
	};
}