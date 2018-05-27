#include "MiniginPCH.h"
#include "PacMan.h"
#include "Score.h"
#include "Lives.h"
#include "TimeManager.h"

dae::PacMan::PacMan(std::shared_ptr<Score> score, std::shared_ptr<Lives> lives, float invincibiltyFrame)
	:Component(false)
	,m_pScore(score)
	,m_pLives(lives)
	,m_InvincibilityTimeMax(invincibiltyFrame)
	,m_InvincibilityTime(0.f)
{
}

void dae::PacMan::Initialize()
{
	m_pLives.lock()->SetLives(m_Lives);
}

void dae::PacMan::Update()
{
	if(m_InvincibilityTime > 0.f)
	{
		m_InvincibilityTime -= dae::TimeManager::GetInstance().GetDeltaTime();
	}
}

void dae::PacMan::Render() const
{
}

void dae::PacMan::DetractLife()
{
	if (m_InvincibilityTime <= 0.0f)
	{
		m_Lives--;
		m_pLives.lock()->SetLives(m_Lives);
		m_InvincibilityTime = m_InvincibilityTimeMax;
	}
}

void dae::PacMan::AddScore(int score)
{
	m_pScore.lock()->AddScore(score);
}
