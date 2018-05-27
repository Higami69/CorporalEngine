#pragma once

namespace dae
{
	class Command
	{
	public:
		Command();
		//virtual ~Command();
		virtual void Execute() = 0;


		Command(Command& other) = delete;
		Command& operator=(Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(Command&& other) = delete;
	};

	class CollisionComponent;

	class TriggerCommand
	{
	public:
		TriggerCommand();
		virtual bool Execute(CollisionComponent& other) = 0;
	};

	enum class Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	class GameObject;

	class MoveCommand : public Command
	{
	public:
		MoveCommand(float speed, Direction dir, std::shared_ptr<GameObject> obj);
		void Execute() override;

	private:
		float m_Speed;
		Direction m_Dir;
		std::weak_ptr<GameObject> m_GameObject;
	};

	class Score;

	class PillCommand : public TriggerCommand
	{
	public:
		PillCommand(int score, std::shared_ptr<GameObject> obj);
		bool Execute(CollisionComponent& other) override;

	private:
		int m_Score;
		std::weak_ptr<GameObject> m_pGameObject;
	};

	class PowerUpPill;

	class PowerUpPillCommand : public TriggerCommand
	{
	public:
		PowerUpPillCommand(std::shared_ptr<PowerUpPill> pill, std::shared_ptr<GameObject> obj);
		bool Execute(CollisionComponent& other) override;

	private:
		std::weak_ptr<PowerUpPill> m_pPill;
		std::weak_ptr<GameObject> m_pGameObject;
	};

	enum class SceneType
	{
		ONE_PLAYER,
		TWO_PLAYER,
		VERSUS
	};

	class SceneSwapCommand : public Command
	{
	public:
		SceneSwapCommand(SceneType type);
		void Execute() override;

	private:
		SceneType m_Type;
	};
}