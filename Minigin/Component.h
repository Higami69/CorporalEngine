#pragma once

namespace dae {
	class GameObject;

	class Component
	{
	public:
		virtual void Initialize() = 0;

		virtual void Update() = 0;
		virtual void Render() const = 0;

		void SetGameObject(std::shared_ptr<dae::GameObject> obj);
		bool InteractsWithGameObjects() const { return m_Interacts; };

		Component(bool interacts);
		virtual ~Component();
		Component(const Component& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(Component&& other) = delete;

		std::weak_ptr<dae::GameObject> GetGameObject();
	protected:

	private:
		std::weak_ptr<dae::GameObject> m_pGameObject;
		bool m_Interacts;
	};
}