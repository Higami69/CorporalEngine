#include "MiniginPCH.h"
#include "ThreadManager.h"
#include "ThreadComponent.h"

void dae::ThreadManager::Update()
{
	for(auto comp : m_pComponents)
	{
		comp->Unlock();
	}
}

void dae::ThreadManager::Add(std::shared_ptr<ThreadComponent> comp)
{
	m_pComponents.push_back(comp);
}

void dae::ThreadManager::BeginThreads(std::string sceneName)
{
	for(auto comp : m_pComponents)
	{
		if(comp->isInScene(sceneName)) comp->BeginThread();
	}
}

void dae::ThreadManager::CloseThreads(std::string sceneName)
{
	for (auto comp : m_pComponents)
	{
		if(comp->isInScene(sceneName)) comp->Close();
	}
}
