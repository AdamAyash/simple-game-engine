#include <GL/glew.h>
#include "graphics/GraphicsAPI.h"
#include "graphics/ShaderProgram.h"
#include <fstream>
#include <sstream>

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
        if(!checkCompileErrors(vertex, "VERTEX"))
            return nullptr;
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        if(!checkCompileErrors(fragment, "FRAGMENT"))
            return nullptr;
        // shader Program
        GLuint shaderPorgramID = glCreateProgram();
        glAttachShader(shaderPorgramID, vertex);
        glAttachShader(shaderPorgramID, fragment);
        glLinkProgram(shaderPorgramID);
        if(!checkCompileErrors(shaderPorgramID, "PROGRAM"))
            return nullptr;
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return std::make_shared<ShaderProgram>(shaderPorgramID);
	}

    void GraphicsAPI::BindShaderProgram(ShaderProgram* shaderProgram)
    {
        shaderProgram->Bind();
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