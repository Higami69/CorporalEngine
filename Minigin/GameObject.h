#pragma once
#include <memory>

#include "TransformComponent.h"
#include "Texture2D.h"
#include "Component.h"

namespace dae
{
	class GameObject : public std::enable_shared_from_this<dae::GameObject>
	{
	public:
		void Initialize();

		void Update();
		void LateUpdate();
		void Render() const;

		void SetPosition(float x, float y);
		TransformComponent& GetTransformComponent();

		void AddComponent(std::shared_ptr<dae::Component>& comp);
		void RemoveComponent(std::shared_ptr<dae::Component>& comp);
		template <class T>
		std::shared_ptr<T> GetComponent();

		bool IsThreaded() const { return m_IsThreaded; };

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		TransformComponent mTransformComponent;
		std::vector<std::shared_ptr<Component>> m_pComponents;
		bool m_IsThreaded;
	};

	template <class T>
	std::shared_ptr<T> GameObject::GetComponent()
	{
		const type_info& ti = typeid(T);
		for(auto p: m_pComponents)
		{
			if(typeid(*p) == ti)
			{
				return std::dynamic_pointer_cast<T>(p);
			}
		}

		return nullptr;
	}
}
