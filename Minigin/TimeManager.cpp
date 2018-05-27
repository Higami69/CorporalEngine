#include "MiniginPCH.h"
#include "TimeManager.h"

void dae::TimeManager::Update()
{
	auto now = std::chrono::steady_clock::now();
	m_DeltaTime = (float)std::chrono::duration_cast<std::chrono::milliseconds>(now - m_PreviousTimePoint).count();
	m_PreviousTimePoint = now;
	//if (m_DeltaTime > 0.1f) m_DeltaTime = 0.1f; //Cap it to a realistic value to prevent bugs

	m_FpsUpdateTime -= m_DeltaTime;
	if(m_FpsUpdateTime <= 0.0f)
	{
		m_FpsUpdateTime = m_FpsUpdateTimeMax;
		m_FPS = int(1000.f / m_DeltaTime);
	}
}

float dae::TimeManager::GetDeltaTime() const
{
	return m_DeltaTime / 1000.f;
}

int dae::TimeManager::GetFPS() const
{
	return m_FPS;
}
