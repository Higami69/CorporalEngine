#pragma once
#include "Component.h"
#include <thread>
#include <mutex>

namespace dae
{
	class GameObject;

	class ThreadComponent : public Component, public std::enable_shared_from_this<ThreadComponent>
	{
	public:
		ThreadComponent(int seed, std::string sceneName);

		void Initialize() override;;
		void Update() override;
		void Render() const override;

		void BeginThread();
		void Close();
		void Unlock();

		int GetSeed() const { return m_Seed; };
		bool isInScene(std::string sceneName) const { return sceneName == m_SceneName; };

	private:
		void ThreadUpdate(bool& isRunning, bool& isLocked);

		std::thread m_Thread;
		std::weak_ptr<GameObject> m_pGameObject;
		bool m_IsRunning, m_IsLocked;
		int m_Seed;
		std::string m_SceneName;
	};
}
