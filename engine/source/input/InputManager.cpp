#include "input/InputManager.h"

namespace engine
{
	void InputManager::SetKeyPressed(int key, bool pressed)
	{
		if (key < 0 || key >= (int)m_keys.size())
			return;

		m_keys[key] = pressed;
	}

	bool InputManager::IsKeyPressed(int key)
	{
		if (key < 0 || key >= (int)m_keys.size())
			return false;

		return m_keys[key];
	}
}
