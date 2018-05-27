#pragma once

namespace dae {
	class Scene;
	class Score;
	class PacMan;
	class PowerUpPill;
}

class Game
{
public:
	static void LoadGame();
private:
	static void LoadLevel(std::string path, dae::Scene& scene, std::shared_ptr<dae::PowerUpPill> powerUp);
	static void SpawnGhost(float x, float y, dae::Scene& scene, std::shared_ptr<dae::PacMan> pacman, std::shared_ptr<dae::PowerUpPill> powerUp,
		std::shared_ptr<dae::PacMan> pacwoman = nullptr);
};
