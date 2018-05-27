#include "MiniginPCH.h"
#include "Component.h"

void dae::Component::SetGameObject(std::shared_ptr<dae::GameObject> obj)
{
	m_pGameObject = obj;
}

dae::Component::Component(bool interacts)
	:m_Interacts(interacts)
{
}

dae::Component::~Component()
{

}

std::weak_ptr<dae::GameObject> dae::Component::GetGameObject()
{
	return m_pGameObject;
}
