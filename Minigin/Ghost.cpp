#include "MiniginPCH.h"
#include "Ghost.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "ThreadComponent.h"
#include "TimeManager.h"
#include "CollisionComponent.h"
#include "PacMan.h"

dae::Ghost::Ghost(float speed, std::shared_ptr<dae::PacMan> pacman, std::shared_ptr<dae::PacMan> pacwoman)
	:Component(true)
	,m_Speed(speed)
	,m_IsScared(false)
	,m_pPacman(pacman)
	,m_pPacWoman(pacwoman)
{
}

void dae::Ghost::Initialize()
{
	m_pRenderComponent = GetGameObject().lock()->GetComponent<dae::RenderComponent>();
	m_pRenderComponent.lock()->SetTextureEnabled("ScaredGhost", false);
	m_pThreadComponent = GetGameObject().lock()->GetComponent<dae::ThreadComponent>();
	m_pCollisionComponent = GetGameObject().lock()->GetComponent<dae::CollisionComponent>();
	m_pPacmanCollisionComponent = m_pPacman.lock()->GetGameObject().lock()->GetComponent<dae::CollisionComponent>();
	if(m_pPacWoman.lock() != nullptr) m_pPacWomanCollisionComponent = m_pPacWoman.lock()->GetGameObject().lock()->GetComponent<dae::CollisionComponent>();
	auto pos = GetGameObject().lock()->GetTransformComponent().GetPosition();
	m_InitialPos.x = pos.x;
	m_InitialPos.y = pos.y;
}

void dae::Ghost::Update()
{
	//MOVEMENT
	//-------------------------
	srand(m_pThreadComponent.lock()->GetSeed() * unsigned int(time(NULL)));

	int dir = rand() % 4;
	auto pos = GetGameObject().lock()->GetTransformComponent().GetPosition();
	float change = (m_Speed * dae::TimeManager::GetInstance().GetDeltaTime());
	if (change > m_Speed / 10.f) change = m_Speed / 10.f; //Stop it from zooming off at start
	switch(dir)
	{
	case 0: //Up
		GetGameObject().lock()->SetPosition(pos.x, pos.y + change);
		break;
	case 1: //Down
		GetGameObject().lock()->SetPosition(pos.x, pos.y - change);
	case 2: //Left
		GetGameObject().lock()->SetPosition(pos.x - change, pos.y);
		break;
	case 3: //Right
		GetGameObject().lock()->SetPosition(pos.x + change, pos.y);
		break;
	}

	//Check for collision with pacman
	if(m_pCollisionComponent.lock()->CheckCollision(m_pPacmanCollisionComponent.lock()->GetArea()))
	{
		if(m_IsScared)
		{
			Reset();
			m_pPacman.lock()->AddScore(5);
		}
		else
		{
			m_pPacman.lock()->DetractLife();
		}
	}

	//Check for collision with pacwoman
	if (m_pPacWoman.lock() != nullptr && m_pCollisionComponent.lock()->CheckCollision(m_pPacWomanCollisionComponent.lock()->GetArea()))
	{
		if (m_IsScared)
		{
			Reset();
			m_pPacWoman.lock()->AddScore(5);
		}
		else
		{
			m_pPacWoman.lock()->DetractLife();
		}
	}
}

void dae::Ghost::Render() const
{
}

void dae::Ghost::SetScared(bool scared)
{
	m_IsScared = scared;
	if(scared)
	{
		m_pRenderComponent.lock()->SetTextureEnabled("Ghost", false);
		m_pRenderComponent.lock()->SetTextureEnabled("ScaredGhost", true);
	}
	else
	{
		m_pRenderComponent.lock()->SetTextureEnabled("Ghost", true);
		m_pRenderComponent.lock()->SetTextureEnabled("ScaredGhost", false);
	}
}

void dae::Ghost::Reset()
{
	GetGameObject().lock()->SetPosition(m_InitialPos.x, m_InitialPos.y);
	m_IsScared = false;
	m_pRenderComponent.lock()->SetTextureEnabled("Ghost", true);
	m_pRenderComponent.lock()->SetTextureEnabled("ScaredGhost", false);
}
