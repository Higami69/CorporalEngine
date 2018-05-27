#include "MiniginPCH.h"
#include "ThreadComponent.h"
#include "GameObject.h"
#include "ThreadManager.h"

dae::ThreadComponent::ThreadComponent(int seed, std::string sceneName)
	:Component(false)
	,m_IsRunning(true)
	,m_Seed(seed)
	,m_IsLocked(false)
	,m_SceneName(sceneName)
{
}

void dae::ThreadComponent::Initialize()
{
	m_pGameObject = GetGameObject();
	dae::ThreadManager::GetInstance().Add(shared_from_this());
}

void dae::ThreadComponent::Update()
{
}

void dae::ThreadComponent::Render() const
{
	//Rendering is still handled by the SceneManager
}

void dae::ThreadComponent::BeginThread()
{
	m_IsRunning = true;
	m_Thread = std::thread(&ThreadComponent::ThreadUpdate, this, std::ref(m_IsRunning),std::ref(m_IsLocked));
}

void dae::ThreadComponent::Close()
{
	m_IsRunning = false;
	m_Thread.join();
}

void dae::ThreadComponent::Unlock()
{
	m_IsLocked = false;
}

void dae::ThreadComponent::ThreadUpdate(bool& isRunning, bool& isLocked)
{
	while (isRunning)
	{
		if (!isLocked)
		{
			isLocked = true;
			m_pGameObject.lock()->Update();
			m_pGameObject.lock()->LateUpdate();
		}
	}
}
