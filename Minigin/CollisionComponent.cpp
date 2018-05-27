#include "MiniginPCH.h"
#include "CollisionComponent.h"
#include "GameObject.h"
#include <valarray>
#include "CollisionManager.h"
#include "Command.h"

dae::CollisionComponent::CollisionComponent(float width, float height, bool isStatic, std::string sceneName)
	:Component(true)
	,m_IsStatic(isStatic)
	,m_IsTrigger(false)
	,m_PrevX(0.0f)
	,m_PrevY(0.0f)
	,m_pTriggerCommand(nullptr)
	,m_IsOneTimeTrigger(false)
	,m_IsOneTimeUsed(false)
	,m_SceneName(sceneName)
{
	auto halfWidth = width / 2;
	auto halfHeight = height / 2;
	m_CollisionArea = AABB(0, 0, halfWidth, halfHeight);
}

void dae::CollisionComponent::Initialize()
{
	CollisionManager::GetInstance().AddComponent(shared_from_this(),m_SceneName);
}

void dae::CollisionComponent::Update()
{
	m_PrevX = m_CollisionArea.Ax;
	m_PrevY = m_CollisionArea.Ay;

	auto pos = GetGameObject().lock()->GetTransformComponent().GetPosition();
	m_CollisionArea.Ax = pos.x;
	m_CollisionArea.Ay = pos.y;
}

void dae::CollisionComponent::Render() const
{
}

void dae::CollisionComponent::SetTrigger(std::shared_ptr<TriggerCommand> command, bool isOneTime)
{
	if(!m_IsStatic) throw std::exception("CollisionComponent::SetTrigger > Trigger must be static!\n");

	m_IsTrigger = true;
	m_pTriggerCommand = command;
	m_IsOneTimeTrigger = isOneTime;
}

bool dae::CollisionComponent::CheckCollision(const AABB& other)
{
	if (std::abs(m_CollisionArea.Ax - other.Ax) > (m_CollisionArea.Bx + other.Bx)) return false;
	if (std::abs(m_CollisionArea.Ay - other.Ay) > (m_CollisionArea.By + other.By)) return false;

	return true;
}

void dae::CollisionComponent::ApplyCollision()
{
	GetGameObject().lock()->SetPosition(m_PrevX, m_PrevY);
	m_CollisionArea.Ax = m_PrevX;
	m_CollisionArea.Ay = m_PrevY;
}

void dae::CollisionComponent::ApplyTrigger(std::shared_ptr<CollisionComponent> other)
{
	if (!m_IsOneTimeUsed)
	{
		if (m_pTriggerCommand->Execute(*other) && m_IsOneTimeTrigger) m_IsOneTimeUsed = true;
	}
}
