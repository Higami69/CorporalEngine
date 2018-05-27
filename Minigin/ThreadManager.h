#pragma once
#include "Singleton.h"

namespace dae
{
	class ThreadComponent;

	class ThreadManager : public Singleton<ThreadManager>
	{
	public:

		void Update();

		void Add(std::shared_ptr<ThreadComponent> comp);
		void BeginThreads(std::string sceneName);
		void CloseThreads(std::string sceneName);

	private:
		std::vector<std::shared_ptr<ThreadComponent>> m_pComponents;
	};
}
