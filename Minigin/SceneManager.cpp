#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ThreadManager.h"


void dae::SceneManager::Update()
{
	m_pActiveScene->Update();
}

void dae::SceneManager::LateUpdate()
{
	m_pActiveScene->LateUpdate();
}

void dae::SceneManager::Render()
{

	m_pActiveScene->Render();

}

void dae::SceneManager::SetActiveScene(std::string id)
{
	auto& threadManager = dae::ThreadManager::GetInstance();
	threadManager.CloseThreads(m_pActiveScene->GetName());
	m_pActiveScene = mScenes[id];
	threadManager.BeginThreads(m_pActiveScene->GetName());
}

std::string dae::SceneManager::GetActiveSceneName() const
{
	return m_pActiveScene->GetName();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	mScenes[name] = scene;
	if(mScenes.size() == 1) m_pActiveScene = scene;
	return *scene;
}

void dae::SceneManager::Initialize()
{
	for (auto scene : mScenes)
	{
		auto s = scene.second;
		s->Initialize();
	}
}
