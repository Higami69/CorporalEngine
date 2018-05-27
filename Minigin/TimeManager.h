#pragma once
#include "Singleton.h"
#include <chrono>

namespace dae
{
	class TimeManager final : public Singleton<TimeManager>
	{
	public:
		void Update();

		float GetDeltaTime() const;
		int GetFPS() const;
		
	private:
		std::chrono::time_point<std::chrono::steady_clock> m_PreviousTimePoint;
		float m_DeltaTime = 0.f, m_FpsUpdateTime = 0.f, m_FpsUpdateTimeMax = 50.f;
		int m_FPS = 0;
	};
}
