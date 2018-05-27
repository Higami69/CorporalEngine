#include "MiniginPCH.h"
#include "PlayerGhost.h"
#include "PacMan.h"
#include "CollisionComponent.h"
#include "GameObject.h"
#include "RenderComponent.h"

dae::PlayerGhost::PlayerGhost(std::shared_ptr<PacMan> pacman)
	:Component(false)
	,m_pPacman(pacman)
	,m_IsScared(false)
{
}

void dae::PlayerGhost::Initialize()
{
	m_pPacmanColl = m_pPacman.lock()->GetGameObject().lock()->GetComponent<dae::CollisionComponent>();
	m_pCollComp = GetGameObject().lock()->GetComponent<dae::CollisionComponent>();
	m_pRenderComp = GetGameObject().lock()->GetComponent<dae::RenderComponent>();
	m_pRenderComp.lock()->SetTextureEnabled("ScaredGhost", false);

}

void dae::PlayerGhost::Update()
{
	if (m_pCollComp.lock()->CheckCollision(m_pPacmanColl.lock()->GetArea()))
	{
		if (m_IsScared)
		{
			m_pRenderComp.lock()->SetTextureEnabled("Ghost", true);
			m_pRenderComp.lock()->SetTextureEnabled("ScaredGhost", false);
			m_IsScared = false;
			m_pPacman.lock()->AddScore(5);
			GetGameObject().lock()->SetPosition(300, 390);
		}
		else
		{
			m_pPacman.lock()->DetractLife();
		}
	}
}

void dae::PlayerGhost::Render() const
{
}

void dae::PlayerGhost::SetScared(bool scared)
{
	m_IsScared = scared;
	if (scared)
	{
		m_pRenderComp.lock()->SetTextureEnabled("Ghost", false);
		m_pRenderComp.lock()->SetTextureEnabled("ScaredGhost", true);
	}
	else
	{
		m_pRenderComp.lock()->SetTextureEnabled("Ghost", true);
		m_pRenderComp.lock()->SetTextureEnabled("ScaredGhost", false);
	}
}
