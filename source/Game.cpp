#include "Game.h"
#include <iostream>
#include <GLFW/glfw3.h>

bool Game::Init() 
{
	auto vertexShader = R"(
	#version 330 core
	layout (location = 0) in vec3 oPosition;
	
	void main()
	{
		gl_Position = vec4(oPosition, 1.0);
	}
)";

	auto fragmentShader = R"(
	#version 330 core
	out vec4 color;
	
	void main()
	{
		color = vec4(1.0, 1.0, 1.0, 1.0);
	}
)";

	auto& grpahicsAPI = engine::Engine::GetInstance().GetGraphicsAPI();
	auto shaderProgram = grpahicsAPI.CreateShaderProgram(vertexShader, fragmentShader);
	m_Material.SetShaderProgram(shaderProgram);

	std::vector<float> vertices =
	{
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f
	};

	std::vector<unsigned int> indices =
	{
		0, 1, 2,
		0, 2, 3
	};

	engine::VertexLayout vertexLayout;
	vertexLayout.elements.push_back({
		1,
		3,
		GL_FLOAT,
		0
		});

	vertexLayout.elements.push_back({
	0,
	3,
	GL_FLOAT,
	sizeof(float) * 3
		});

	vertexLayout.stride = sizeof(float) * 6;
	m_mesh = std::make_unique<engine::Mesh>(vertexLayout, vertices, indices);

	return true;
}

void Game::Update(float deltaTime)
{
	auto& input = engine::Engine::GetInstance().GetInputManager();
	if (input.IsKeyPressed(GLFW_KEY_A))
	{
		std::cout << "[A] button is pressed" << std::endl;
	}
}

void Game::Destroy()
{

}