#include "MiniginPCH.h"
#include "CollisionManager.h"
#include "CollisionComponent.h"
#include "SceneManager.h"

void dae::CollisionManager::Update()
{
	std::string id = dae::SceneManager::GetInstance().GetActiveSceneName();
	auto vDynamic = m_DynamicComponents[id];
	auto vStatic = m_StaticComponents[id];
	for(auto dynamic : vDynamic)
	{
		for(auto stat : vStatic)
		{
			if(dynamic->CheckCollision(stat->GetArea()))
			{
				stat->IsTrigger() ? stat->ApplyTrigger(dynamic) : dynamic->ApplyCollision();
			}
		}
	}
}

void dae::CollisionManager::Destroy()
{
	m_StaticComponents.clear();
	m_DynamicComponents.clear();
}

void dae::CollisionManager::AddComponent(std::shared_ptr<CollisionComponent> comp, std::string sceneName)
{
	if (comp->IsStatic()) m_StaticComponents[sceneName].push_back(comp);
	else m_DynamicComponents[sceneName].push_back(comp);
}
