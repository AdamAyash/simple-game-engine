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