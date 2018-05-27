#pragma once
#include "Component.h"

namespace dae
{
	class Ghost;
	class PlayerGhost;

	class PowerUpPill : public Component
	{
	public:
		PowerUpPill(float powerUpTime);

		void Initialize() override;
		void Update() override;
		void Render() const override;

		void AddGhost(std::shared_ptr<Ghost> ghost);
		void AddGhost(std::shared_ptr<PlayerGhost> ghost);
		void WakeUp();

	private:
		std::vector<std::weak_ptr<Ghost>> m_pGhosts;
		std::weak_ptr<PlayerGhost> m_pPlayerGhost;
		float m_PowerUpTime, m_PowerUpTimeMax;
		bool m_Update;
	};
}
