#pragma once
#include "Component.h"

namespace dae
{
	class RenderComponent;
	class ThreadComponent;
	class PacMan;
	class CollisionComponent;

	struct Float2
	{
		float x, y;
	};

	class Ghost : public Component
	{
	public:
		Ghost(float speed, std::shared_ptr<PacMan> pacman, std::shared_ptr<PacMan> pacwoman = nullptr);

		void Initialize() override;
		void Update() override;
		void Render() const override;

		void SetScared(bool scared);

	private:
		void Reset();

		std::weak_ptr<RenderComponent> m_pRenderComponent;
		std::weak_ptr<ThreadComponent> m_pThreadComponent;
		std::weak_ptr<CollisionComponent> m_pCollisionComponent, m_pPacmanCollisionComponent, m_pPacWomanCollisionComponent;
		std::weak_ptr<PacMan> m_pPacman, m_pPacWoman;
		bool m_IsScared;
		float m_Speed;
		Float2 m_InitialPos;
	};
}
