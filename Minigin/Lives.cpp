#include "MiniginPCH.h"
#include "Lives.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "SceneManager.h"

dae::Lives::Lives()
	:Component(false)
{
}

void dae::Lives::Initialize()
{
	m_pText = GetGameObject().lock()->GetComponent<dae::TextComponent>();
}

void dae::Lives::Update()
{
}

void dae::Lives::Render() const
{
}

void dae::Lives::SetLives(int lives)
{
	m_Lives = lives;
	std::string s = "Lives: " + std::to_string(m_Lives);
	m_pText.lock()->SetText(s);
	if (m_Lives == 0) dae::SceneManager::GetInstance().SetActiveScene("GameOver");
}
