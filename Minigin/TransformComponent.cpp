#include "MiniginPCH.h"
#include "TransformComponent.h"


dae::TransformComponent::TransformComponent()
	:Component(false)
{
}

void dae::TransformComponent::Initialize()
{
}

void dae::TransformComponent::Update()
{
}

void dae::TransformComponent::Render() const
{
}

void dae::TransformComponent::SetPosition(const float x, const float y, const float z)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = z;
}
