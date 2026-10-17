#include "Engine.h"
#include "Application.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace engine
{
	void keyCallback(GLFWwindow* window, int key, int, int action, int)
	{
		auto& inputManager = engine::Engine::GetInstance().GetInputManager();
		if (action == GLFW_PRESS)
		{
			inputManager.SetKeyPressed(key, true);
		}
		else if(action == GLFW_RELEASE)
		{
			inputManager.SetKeyPressed(key, false);
		}
	}

	Engine& Engine::GetInstance()
	{
		static Engine instance;
		return instance;
	}

	bool Engine::Init(int width, int height)
	{
		if (!m_oApplication)
			return false;

		if (!glfwInit())
		{
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(width, height, "Application", nullptr, nullptr);
		if (!m_window)
		{
			glfwTerminate();
			return false;
		}

		glfwSetKeyCallback(m_window, keyCallback);

		glfwMakeContextCurrent(m_window);
		
		if (glewInit() != GLEW_OK)
		{
			glfwTerminate();
			return false;
		}

		return m_oApplication->Init();
	}

	void Engine::Run()
	{
		if (!m_oApplication)
			return;

		m_lastTimePoint = std::chrono::high_resolution_clock::now();
		while (!glfwWindowShouldClose(m_window) && !m_oApplication->NeedsToBeClosed())
		{
			glfwPollEvents();

			auto now = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(now - m_lastTimePoint).count();
			m_lastTimePoint = now;

			m_oApplication->Update(deltaTime);

			glfwSwapBuffers(m_window);
		}
	}

	void Engine::Destroy()
	{
		if (m_oApplication)
		{
			m_oApplication->Destroy();
			m_oApplication.reset();
			glfwTerminate();
			m_window = nullptr;
		}
	}

	void Engine::SetApplication(Application* application)
	{
		m_oApplication.reset(application);
	}

	Application* Engine::GetApplication()
	{
		return m_oApplication.get();
	}

	InputManager& Engine::GetInputManager()
	{
		return m_inputManager;
	}

	GraphicsAPI& Engine::GetGraphicsAPI()
	{
		return m_graphicsAPI;
	}
}