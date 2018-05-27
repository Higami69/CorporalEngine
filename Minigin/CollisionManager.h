#pragma once
#include "Singleton.h"
#include <map>

namespace dae
{
	class CollisionComponent;

	class CollisionManager : public Singleton<CollisionManager>
	{
	public:
		void Update();
		void Destroy();
		void AddComponent(std::shared_ptr<CollisionComponent> comp, std::string scene);
	private:
		std::map<std::string,std::vector<std::shared_ptr<CollisionComponent>>> m_StaticComponents, m_DynamicComponents;
	};
}
