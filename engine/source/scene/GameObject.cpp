#include "scene/GameObject.h"

namespace engine
{
	void GameObject::Update(float deltaTime)
	{
		for (auto it = m_childern.begin(); it != m_childern.end();)
		{
			if ((*it)->IsAlive())
			{
				(*it)->Update(deltaTime);
				++it;
			}
			else 
			{
				it = m_childern.erase(it);
			}
		}
	}

	const std::string& GameObject::GetName() const
	{
		return m_name;
	}

	void GameObject::SetName(const std::string& name)
	{
		m_name = name;
	}

	GameObject* GameObject::GetParent()
	{
		return m_parent;
	}

	bool GameObject::IsAlive() const
	{
		return m_isAlive;
	}

	void GameObject::MarkForDestroy()
	{
		m_isAlive = false;
	}
}
