#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"
#include <algorithm>
#include "ThreadComponent.h"

dae::GameObject::GameObject()
	:mTransformComponent()
	,m_IsThreaded(false)
{
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Initialize()
{
	for(auto c : m_pComponents)
	{
		c->Initialize();
	}
}

void dae::GameObject::Update()
{
	for(auto p : m_pComponents)
	{
		if(!p->InteractsWithGameObjects())
			p->Update();
	}
}

void dae::GameObject::LateUpdate()
{
	for (auto p : m_pComponents)
	{
		if (p->InteractsWithGameObjects())
			p->Update();
	}
}

void dae::GameObject::Render() const
{
	for (auto p : m_pComponents)
	{
		p->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	mTransformComponent.SetPosition(x, y, 0.0f);
}

dae::TransformComponent& dae::GameObject::GetTransformComponent()
{
	return mTransformComponent;
}

void dae::GameObject::AddComponent(std::shared_ptr<dae::Component>& comp)
{
	m_pComponents.push_back(comp);
	if (std::dynamic_pointer_cast<dae::ThreadComponent>(comp) != nullptr) m_IsThreaded = true;
	comp->SetGameObject(shared_from_this());
}

void dae::GameObject::RemoveComponent(std::shared_ptr<dae::Component>& comp)
{
	for(auto p : m_pComponents)
	{
		if(p == comp)
		{
			m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), p));
		}
	}
}
