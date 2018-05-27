#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name) : mName(name) {}

dae::Scene::~Scene() = default;

void dae::Scene::Add(const std::shared_ptr<GameObject>& object)
{
	mObjects.push_back(object);
}

void dae::Scene::Initialize()
{
	for(auto object : mObjects)
	{
		object->Initialize();
	}
}

void dae::Scene::Update()
{
	for(auto gameObject : mObjects)
	{
		if(!gameObject->IsThreaded()) gameObject->Update();
	}
}

void dae::Scene::LateUpdate()
{
	for (auto gameObject : mObjects)
	{
		gameObject->LateUpdate();
	}
}

void dae::Scene::Render() const
{
	for (const auto gameObject : mObjects)
	{
		gameObject->Render();
	}
}

