#pragma once
#include "Component.h"

namespace dae
{
	class Score;
	class Lives;

	class PacMan : public Component
	{
	public:
		PacMan(std::shared_ptr<Score> score, std::shared_ptr<Lives> lives, float invincibiltyFrame);

		void Initialize() override;
		void Update() override;
		void Render() const override;

		void DetractLife();
		void AddScore(int score);
	private:
		int m_Lives = 3;
		float m_InvincibilityTime, m_InvincibilityTimeMax;
		std::weak_ptr<Score> m_pScore;
		std::weak_ptr<Lives> m_pLives;
	};
}
