#include "MiniginPCH.h"
#include "PowerUpPill.h"
#include "Ghost.h"
#include "TimeManager.h"
#include "PlayerGhost.h"

dae::PowerUpPill::PowerUpPill(float powerUpTime)
	:Component(false)
	,m_PowerUpTime(0.0f)
	,m_PowerUpTimeMax(powerUpTime)
	,m_Update(false)
{
}

void dae::PowerUpPill::Initialize()
{
}

void dae::PowerUpPill::Update()
{
	if(m_Update)
	{
		m_PowerUpTime -= dae::TimeManager::GetInstance().GetDeltaTime();
		if(m_PowerUpTime <= 0.0f)
		{
			m_Update = false;
			for(auto g : m_pGhosts)
			{
				g.lock()->SetScared(false);
			}

			if (m_pPlayerGhost.lock() != nullptr) m_pPlayerGhost.lock()->SetScared(false);
		}
	}
}

void dae::PowerUpPill::AddGhost(std::shared_ptr<PlayerGhost> ghost)
{
	m_pPlayerGhost = ghost;
}

void dae::PowerUpPill::Render() const
{
}

void dae::PowerUpPill::AddGhost(std::shared_ptr<Ghost> ghost)
{
	m_pGhosts.push_back(ghost);
}

void dae::PowerUpPill::WakeUp()
{
	m_Update = true;
	m_PowerUpTime = m_PowerUpTimeMax;
	for(auto g : m_pGhosts)
	{
		g.lock()->SetScared(true);
	}
	if (m_pPlayerGhost.lock() != nullptr) m_pPlayerGhost.lock()->SetScared(true);
}
