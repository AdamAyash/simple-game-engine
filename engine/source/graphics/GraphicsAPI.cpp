#include <GL/glew.h>
#include "graphics/GraphicsAPI.h"
#include "graphics/ShaderProgram.h"
#include <fstream>
#include <sstream>
#include <render/Material.h>
#include <render/Mesh.h>

namespace engine
{
	std::shared_ptr<ShaderProgram> GraphicsAPI::CreateShaderProgram(const std::string& vertexSourcePath,
		const std::string& fragmentSourcePath)
	{
		const char* vShaderCode = vertexSourcePath.c_str();
		const char* fShaderCode = fragmentSourcePath.c_str();
		// 2. compile shaders
		unsigned int vertex, fragment;
		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		if (!checkCompileErrors(vertex, "VERTEX"))
			return nullptr;
		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		if (!checkCompileErrors(fragment, "FRAGMENT"))
			return nullptr;
		// shader Program
		GLuint shaderPorgramID = glCreateProgram();
		glAttachShader(shaderPorgramID, vertex);
		glAttachShader(shaderPorgramID, fragment);
		glLinkProgram(shaderPorgramID);
		if (!checkCompileErrors(shaderPorgramID, "PROGRAM"))
			return nullptr;
		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return std::make_shared<ShaderProgram>(shaderPorgramID);
	}

	GLuint GraphicsAPI::CreateVertexBuffer(const std::vector<float>& vertices)
	{
		GLuint vbo = 0;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		return vbo;
	}

	GLuint GraphicsAPI::CreateIndexBuffer(const std::vector<uint32_t>& indices)
	{
		GLuint ebo = 0;
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), indices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		return ebo;
	}

	void GraphicsAPI::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void GraphicsAPI::ClearBuffers()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void GraphicsAPI::BindShaderProgram(ShaderProgram* shaderProgram)
	{
		if (shaderProgram)
		{
			shaderProgram->Bind();
		}
	}

	void GraphicsAPI::BindMaterial(Material* material)
	{
		if (material)
			material->Bind();
	}

	void GraphicsAPI::BindMesh(Mesh* mesh)
	{
		if (mesh)
			mesh->Bind();
	}

	void GraphicsAPI::DrawMesh(Mesh* mesh)
	{
		if (mesh)
			mesh->Draw();
	}

	bool GraphicsAPI::checkCompileErrors(unsigned int shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
				return false;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
				return false;
			}
		}
	}
}