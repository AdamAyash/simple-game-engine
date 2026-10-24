#include "TestObject.h"
#include <GLFW/glfw3.h>

TestObject::TestObject()
{
	auto vertexShader = R"(
	#version 330 core
	layout (location = 0) in vec3 oPosition;
	layout (location = 1) in vec3 oColor;

	uniform vec2 uOffset;

	out vec3 ouputColor; 
	
	void main()
	{
		gl_Position = vec4(oPosition.x + uOffset.x, oPosition.y + uOffset.y, oPosition.z, 1.0);
		ouputColor = oColor;
	}
)";

	auto fragmentShader = R"(
	#version 330 core
	out vec4 color;
	in vec3	ouputColor;

	void main()
	{
		color = vec4(ouputColor, 1.0);
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
		0,
		3,
		GL_FLOAT,
		0
		});

	vertexLayout.elements.push_back({
	1,
	3,
	GL_FLOAT,
	sizeof(float) * 3
		});

	vertexLayout.stride = sizeof(float) * 6;
	m_mesh = std::make_shared<engine::Mesh>(vertexLayout, vertices, indices);
}

void TestObject::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	auto& input = engine::Engine::GetInstance().GetInputManager();

	if (input.IsKeyPressed(GLFW_KEY_A))
	{
		m_offsetX -= 0.01f;
	}
	else if (input.IsKeyPressed(GLFW_KEY_D))
	{
		m_offsetX += 0.01f;
	}

	if (input.IsKeyPressed(GLFW_KEY_W))
	{
		m_offsetY += 0.01f;
	}
	else if (input.IsKeyPressed(GLFW_KEY_S))
	{
		m_offsetY -= 0.01f;
	}

	m_Material.SetParam("uOffset", m_offsetX, m_offsetY);

	engine::RenderCommand command;
	command.material = &m_Material;
	command.mesh = m_mesh.get();

	auto& renderQueue = engine::Engine::GetInstance().GetRenderQueue();
	renderQueue.Sumbmit(command);
}