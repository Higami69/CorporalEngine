#pragma once
#include "Component.h"

namespace dae
{
	class PacMan;
	class CollisionComponent;
	class RenderComponent;

	class PlayerGhost : public Component
	{
	public:
		PlayerGhost(std::shared_ptr<PacMan> pacman);

		void Initialize() override;
		void Update() override;
		void Render() const override;

		void SetScared(bool scared);
	private:
		std::weak_ptr<PacMan> m_pPacman;
		std::weak_ptr<CollisionComponent> m_pCollComp, m_pPacmanColl;
		std::weak_ptr<RenderComponent> m_pRenderComp;
		bool m_IsScared;
	};
}
