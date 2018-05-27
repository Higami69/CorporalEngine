#include "MiniginPCH.h"
#include "Score.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "RenderComponent.h"

dae::Score::Score()
	:Component(false)
	,m_Score(0)
{
}

void dae::Score::Initialize()
{
	m_pText = GetGameObject().lock()->GetComponent<TextComponent>();
}

void dae::Score::Update()
{
}

void dae::Score::Render() const
{
}

void dae::Score::AddScore(int score)
{
	m_Score += score;
	std::string s = "Score: " + std::to_string(m_Score);
	m_pText.lock()->SetText(s);
}
