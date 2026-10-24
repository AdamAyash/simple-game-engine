#include "scene/Scene.h"
#include "scene/GameObject.h"

namespace engine
{
	void Scene::Update(float deltaTime)
	{
		for (auto it = m_objects.begin(); it != m_objects.end();)
		{
			if ((*it)->IsAlive())
			{
				(*it)->Update(deltaTime);
				++it;
			}
			else
			{
				it = m_objects.erase(it);
			}
		}
	}

	void Scene::Clear()
	{
		m_objects.clear();
	}

	GameObject* Scene::CreateObject(const std::string& name, GameObject* parent)
	{
		auto obj = new GameObject();
		obj->SetName(name);
		SetParent(obj, parent);

		return obj;
	}

	bool Scene::SetParent(GameObject* obj, GameObject* parent)
	{
		bool result = false;
		auto currentParent = obj->GetParent();

		if (parent == nullptr)
		{
			if (currentParent != nullptr)
			{
				auto it = std::find_if(currentParent->m_childern.begin(),
					currentParent->m_childern.end(),
					[obj](const std::unique_ptr<GameObject>& el) {
						return el.get() == obj;
					}
				);

				if (it != currentParent->m_childern.end())
				{
					m_objects.push_back(std::move(*it));
					obj->m_parent = nullptr;
					currentParent->m_childern.erase(it);

					result = true;
				}
			}
			//No parent currently
			else
			{
				auto it = std::find_if(m_objects.begin(),
					m_objects.end(),
					[obj](const std::unique_ptr<GameObject>& el) {
						return el.get() == obj;
					}
				);

				if (it == m_objects.end())
				{
					std::unique_ptr<GameObject> objHolder(obj);
					m_objects.push_back(std::move(objHolder));

					result = true;
				}
			}
		}
		else
		{
			if (currentParent != nullptr)
			{
				auto it = std::find_if(currentParent->m_childern.begin(),
					currentParent->m_childern.end(),
					[obj](const std::unique_ptr<GameObject>& el) {
						return el.get() == obj;
					}
				);

				if (it != currentParent->m_childern.end())
				{
					bool found = false;
					auto currentElement = parent;

					while (currentElement)
					{
						if (currentElement == obj)
						{
							found = true;
							break;
						}

						currentElement = currentElement->GetParent();
					}

					if (!found)
					{
						parent->m_childern.push_back(std::move(*it));
						obj->m_parent = parent;
						currentElement->m_childern.erase(it);
						result = true;
					}
				}
			}
			else
			{
				auto it = std::find_if(currentParent->m_childern.begin(),
					currentParent->m_childern.end(),
					[obj](const std::unique_ptr<GameObject>& el) {
						return el.get() == obj;
					}
				);

				if (it == m_objects.end())
				{
					std::unique_ptr<GameObject> objHolder(obj);
					parent->m_childern.push_back(std::move(objHolder));
					obj->m_parent = parent;
					result = true;
				}
				else
				{
					bool found = false;
					auto currentElement = parent;

					while (currentElement)
					{
						if (currentElement == obj)
						{
							found = true;
							break;
						}

						currentElement = currentElement->GetParent();
					}

					if (!found)
					{
						parent->m_childern.push_back(std::move(*it));
						obj->m_parent = parent;
						currentElement->m_childern.erase(it);
						result = true;
					}
				}
			}
		}

		return result;
	}
}
