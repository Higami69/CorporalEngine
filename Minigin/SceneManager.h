#pragma once
#include "Singleton.h"
#include <map>

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene & CreateScene(const std::string& name);

		void Initialize();

		void Update();
		void LateUpdate();
		void Render();

		void SetActiveScene(std::string id);
		std::string GetActiveSceneName() const;

	private:
		std::map<std::string, std::shared_ptr<Scene>> mScenes;
		std::shared_ptr<Scene> m_pActiveScene;
	};

}
