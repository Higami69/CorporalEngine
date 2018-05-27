#include "MiniginPCH.h"
#include "FPSDisplay.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "TimeManager.h"

dae::FPSDisplay::FPSDisplay()
	:Component(false)
{
}

void dae::FPSDisplay::Initialize()
{
	m_pText = GetGameObject().lock()->GetComponent<TextComponent>();
}

void dae::FPSDisplay::Update()
{
	std::string s = "FPS: " + std::to_string(TimeManager::GetInstance().GetFPS());
	m_pText.lock()->SetText(s);
}

void dae::FPSDisplay::Render() const
{
}
