#pragma once

#include <GL/glew.h>
#include <memory>
#include <string>
#include <iostream>
#include <vector>


namespace engine
{
	class ShaderProgram;
	class Material;
	class Mesh;

	class GraphicsAPI
	{
	public:
		std::shared_ptr<ShaderProgram> CreateShaderProgram(const std::string& vertexSourcePath,
			const std::string& fragmentSourcePath);

		GLuint CreateVertexBuffer(const std::vector<float>& vertices);
		GLuint CreateIndexBuffer(const std::vector<uint32_t>& indices);

		void SetClearColor(float r, float g, float b, float a);
		void ClearBuffers();
		void BindShaderProgram(ShaderProgram* shaderProgram);
		void BindMaterial(Material* material);
		void BindMesh(Mesh* mesh);
		void DrawMesh(Mesh* mesh);

    private:
        // utility function for checking shader compilation/linking errors.
        // ------------------------------------------------------------------------
		bool checkCompileErrors(unsigned int shader, std::string type);
	};
}