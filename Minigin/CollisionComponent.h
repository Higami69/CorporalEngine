#pragma once
#include "Component.h"

namespace dae
{
	struct AABB
	{
		AABB(float ax, float ay, float bx, float by)
		{
			Ax = ax;
			Ay = ay;
			Bx = bx;
			By = by;
		}
		float Ax, Ay, Bx, By;
	};

	class TriggerCommand;

	class CollisionComponent : public Component, public std::enable_shared_from_this<CollisionComponent>
	{
	public:
		CollisionComponent(float width, float height, bool isStatic, std::string sceneName);

		void Initialize() override;

		void Update() override;
		void Render() const override;
		void SetTrigger(std::shared_ptr<TriggerCommand> command, bool isOneTime);

		bool CheckCollision(const AABB& other);
		bool IsStatic() const { return m_IsStatic; };
		bool IsTrigger() const { return m_IsTrigger; };
		AABB GetArea() const { return m_CollisionArea; };

		void ApplyCollision();
		void ApplyTrigger(std::shared_ptr<CollisionComponent> other);
	private:

		AABB m_CollisionArea{0,0,0,0};
		bool m_IsStatic, m_IsTrigger, m_IsOneTimeTrigger, m_IsOneTimeUsed;
		float m_PrevX, m_PrevY;
		std::shared_ptr<TriggerCommand> m_pTriggerCommand;
		std::string m_SceneName;
	};
}