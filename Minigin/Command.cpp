#include "MiniginPCH.h"
#include "Command.h"
#include "TimeManager.h"
#include "GameObject.h"
#include "Score.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "PacMan.h"
#include "PowerUpPill.h"
#include "SceneManager.h"

dae::Command::Command()
{
}

dae::TriggerCommand::TriggerCommand()
{
}

dae::MoveCommand::MoveCommand(float speed, Direction dir, std::shared_ptr<GameObject> obj)
	:m_Speed(speed)
	,m_Dir(dir)
	,m_GameObject(obj)
{
}

void dae::MoveCommand::Execute()
{
	auto time = &TimeManager::GetInstance();
	auto pos = m_GameObject.lock()->GetTransformComponent().GetPosition();

	switch (m_Dir)
	{
	case Direction::UP:
		pos.y -= m_Speed * time->GetDeltaTime();
		break;
	case Direction::DOWN:
		pos.y += m_Speed * time->GetDeltaTime();
		break;
	case Direction::LEFT:
		pos.x -= m_Speed * time->GetDeltaTime();
		break;
	case Direction::RIGHT:
		pos.x += m_Speed * time->GetDeltaTime();
		break;
	}

	m_GameObject.lock()->SetPosition(pos.x, pos.y);
}

dae::PillCommand::PillCommand(int score, std::shared_ptr<GameObject> obj)
	:m_Score(score)
	,m_pGameObject(obj)
{
}

bool dae::PillCommand::Execute(CollisionComponent& other)
{
	auto pacman = other.GetGameObject().lock()->GetComponent<dae::PacMan>();
	if (pacman != nullptr)
	{
		pacman->AddScore(1);
		m_pGameObject.lock()->GetComponent<dae::RenderComponent>()->RemoveTexture("Tile");
		return true;
	}
	return false;
}

dae::PowerUpPillCommand::PowerUpPillCommand(std::shared_ptr<PowerUpPill> pill, std::shared_ptr<GameObject> obj)
	:TriggerCommand()
	,m_pPill(pill)
	,m_pGameObject(obj)
{
}

bool dae::PowerUpPillCommand::Execute(CollisionComponent& other)
{
	if(other.GetGameObject().lock()->GetComponent<dae::PacMan>() != nullptr)
	{
		m_pPill.lock()->WakeUp();
		m_pGameObject.lock()->GetComponent<dae::RenderComponent>()->RemoveTexture("Tile");
		return true;
	}
	return false;
}

dae::SceneSwapCommand::SceneSwapCommand(SceneType type)
	:Command()
	,m_Type(type)
{
}

void dae::SceneSwapCommand::Execute()
{
	auto& sceneManager = dae::SceneManager::GetInstance();
	switch(m_Type)
	{
	case dae::SceneType::ONE_PLAYER:
		sceneManager.SetActiveScene("MainGame");
		break;
	case dae::SceneType::TWO_PLAYER:
		sceneManager.SetActiveScene("Coop");
		break;
	case dae::SceneType::VERSUS:
		sceneManager.SetActiveScene("Versus");
		break;
	}
}
