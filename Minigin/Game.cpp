#include "MiniginPCH.h"
#include "Game.h"
#include "GameObject.h"
#include "Scene.h"
#include "InputComponent.h"
#include "Command.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "CollisionComponent.h"
#include "TextComponent.h"
#include "Score.h"
#include "FPSDisplay.h"
#include <fstream>
#include "ThreadComponent.h"
#include "Ghost.h"
#include "PacMan.h"
#include "PowerUpPill.h"
#include "Lives.h"
#include "PlayerGhost.h"

void Game::LoadGame()
{
	//Singleplayer scene
	{
		auto& scene = dae::SceneManager::GetInstance().CreateScene("MainGame");

		//Add score
		auto go = std::make_shared<dae::GameObject>();
		std::shared_ptr<dae::Component>comp = std::make_shared<dae::RenderComponent>();
		go->AddComponent(comp);
		auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
		comp = std::make_shared<dae::TextComponent>("REEEEEEE", font);
		go->AddComponent(comp);
		std::shared_ptr<dae::Component> score = std::make_shared<dae::Score>();
		go->AddComponent(score);
		go->SetPosition(10, 10);
		scene.Add(go);

		//Add PowerUp thread
		go = std::make_shared<dae::GameObject>();
		comp = std::make_shared<dae::ThreadComponent>(0,scene.GetName());
		go->AddComponent(comp);
		auto powerUp = std::make_shared<dae::PowerUpPill>(5.f);
		comp = std::dynamic_pointer_cast<dae::Component>(powerUp);
		go->AddComponent(comp);
		scene.Add(go);

		//Add Lives display
		go = std::make_shared<dae::GameObject>();
		comp = std::make_shared<dae::RenderComponent>();
		go->AddComponent(comp);
		comp = std::make_shared<dae::TextComponent>("DefaultString", font);
		go->AddComponent(comp);
		std::shared_ptr<dae::Component> lives = std::make_shared<dae::Lives>();
		go->AddComponent(lives);
		go->SetPosition(100, 10);
		scene.Add(go);

		//Add some tiles for testing
		LoadLevel("../Data/Level.txt", scene, powerUp);

		//Moving Pacman
		go = std::make_shared<dae::GameObject>();
		float speed = 200.f;
		std::shared_ptr<dae::Command> command = std::make_shared<dae::MoveCommand>(speed, dae::Direction::UP, go);
		comp = std::make_shared<dae::InputComponent>(command, dae::InputType::DOWN, SDLK_UP, dae::ControllerButton::LStickUp);
		go->AddComponent(comp);
		command = std::make_shared<dae::MoveCommand>(speed, dae::Direction::DOWN, go);
		comp = std::make_shared<dae::InputComponent>(command, dae::InputType::DOWN, SDLK_DOWN, dae::ControllerButton::LStickDown);
		go->AddComponent(comp);
		command = std::make_shared<dae::MoveCommand>(speed, dae::Direction::RIGHT, go);
		comp = std::make_shared<dae::InputComponent>(command, dae::InputType::DOWN, SDLK_RIGHT, dae::ControllerButton::LStickRight);
		go->AddComponent(comp);
		command = std::make_shared<dae::MoveCommand>(speed, dae::Direction::LEFT, go);
		comp = std::make_shared<dae::InputComponent>(command, dae::InputType::DOWN, SDLK_LEFT, dae::ControllerButton::LStickLeft);
		go->AddComponent(comp);
		comp = std::make_shared<dae::RenderComponent>();
		auto tex = dae::ResourceManager::GetInstance().LoadTexture("Pacman.png");
		(std::dynamic_pointer_cast<dae::RenderComponent>(comp))->AddTexture("Pacman", tex, 0, 0, true);
		go->AddComponent(comp);
		comp = std::make_shared<dae::CollisionComponent>(16.f, 16.f, false,scene.GetName());
		go->AddComponent(comp);
		std::shared_ptr<dae::Component> pacman = std::make_shared<dae::PacMan>(std::dynamic_pointer_cast<dae::Score>(score), std::dynamic_pointer_cast<dae::Lives>(lives), 0.5f);
		go->AddComponent(pacman);
		go->SetPosition(300, 100);
		scene.Add(go);

		//Ghosts
		SpawnGhost(500, 70, scene, std::dynamic_pointer_cast<dae::PacMan>(pacman), powerUp);
		SpawnGhost(100, 70, scene, std::dynamic_pointer_cast<dae::PacMan>(pacman), powerUp);
		SpawnGhost(100, 420, scene, std::dynamic_pointer_cast<dae::PacMan>(pacman), powerUp);
		SpawnGhost(500, 420, scene, std::dynamic_pointer_cast<dae::PacMan>(pacman), powerUp);

		//Add FPS
		go = std::make_shared<dae::GameObject>();
		comp = std::make_shared<dae::RenderComponent>();
		go->AddComponent(comp);
		comp = std::make_shared<dae::TextComponent>("If you can read this I fucked up", font);
		go->AddComponent(comp);
		comp = std::make_shared<dae::FPSDisplay>();
		go->AddComponent(comp);
		go->SetPosition(550, 10);
		scene.Add(go);
	}

	//GameOver Scene
	{
		auto& scene = dae::SceneManager::GetInstance().CreateScene("GameOver");
		auto go = std::make_shared<dae::GameObject>();
		auto tex = dae::ResourceManager::GetInstance().LoadTexture("background.jpg");
		std::shared_ptr<dae::Component> comp = std::make_shared<dae::RenderComponent>();
		(std::dynamic_pointer_cast<dae::RenderComponent>(comp))->AddTexture("Background", tex, 0, 0, false);
		go->AddComponent(comp);
		scene.Add(go);

		go = std::make_shared<dae::GameObject>();
		comp = std::make_shared<dae::RenderComponent>();
		go->AddComponent(comp);
		auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 64);
		comp = std::make_shared<dae::TextComponent>("GAME OVER", font);
		go->AddComponent(comp);
		go->SetPosition(160, 180);
		scene.Add(go);
	}

	//2 player scene Coop
	{
		auto& scene = dae::SceneManager::GetInstance().CreateScene("Coop");

		//Add PowerUp thread
		auto go = std::make_shared<dae::GameObject>();
		std::shared_ptr<dae::Component>comp = std::make_shared<dae::ThreadComponent>(0, scene.GetName());
		go->AddComponent(comp);
		auto powerUp = std::make_shared<dae::PowerUpPill>(5.f);
		comp = std::dynamic_pointer_cast<dae::Component>(powerUp);
		go->AddComponent(comp);
		scene.Add(go);

		//Add some tiles for testing
		LoadLevel("../Data/Level.txt", scene, powerUp);

		//Add score 1
		go = std::make_shared<dae::GameObject>();
		comp = std::make_shared<dae::RenderComponent>();
		go->AddComponent(comp);
		auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);
		comp = std::make_shared<dae::TextComponent>("REEEEEEE", font);
		go->AddComponent(comp);
		std::shared_ptr<dae::Component> score = std::make_shared<dae::Score>();
		go->AddComponent(score);
		go->SetPosition(10, 1);
		scene.Add(go);

		//Add Lives display 1
		go = std::make_shared<dae::GameObject>();
		comp = std::make_shared<dae::RenderComponent>();
		go->AddComponent(comp);
		comp = std::make_shared<dae::TextComponent>("DefaultString", font);
		go->AddComponent(comp);
		std::shared_ptr<dae::Component> lives = std::make_shared<dae::Lives>();
		go->AddComponent(lives);
		go->SetPosition(100, 6);
		scene.Add(go);

		//Moving Pacman 1
		go = std::make_shared<dae::GameObject>();
		float speed = 200.f;
		std::shared_ptr<dae::Command> command = std::make_shared<dae::MoveCommand>(speed, dae::Direction::UP, go);
		comp = std::make_shared<dae::InputComponent>(command, dae::InputType::DOWN, SDLK_UP, dae::ControllerButton::NONE);
		go->AddComponent(comp);
		command = std::make_shared<dae::MoveCommand>(speed, dae::Direction::DOWN, go);
		comp = std::make_shared<dae::InputComponent>(command, dae::InputType::DOWN, SDLK_DOWN, dae::ControllerButton::NONE);
		go->AddComponent(comp);
		command = std::make_shared<dae::MoveCommand>(speed, dae::Direction::RIGHT, go);
		comp = std::make_shared<dae::InputComponent>(command, dae::InputType::DOWN, SDLK_RIGHT, dae::ControllerButton::NONE);
		go->AddComponent(comp);
		command = std::make_shared<dae::MoveCommand>(speed, dae::Direction::LEFT, go);
		comp = std::make_shared<dae::InputComponent>(command, dae::InputType::DOWN, SDLK_LEFT, dae::ControllerButton::NONE);
		go->AddComponent(comp);
		comp = std::make_shared<dae::RenderComponent>();
		auto tex = dae::ResourceManager::GetInstance().LoadTexture("Pacman.png");
		(std::dynamic_pointer_cast<dae::RenderComponent>(comp))->AddTexture("Pacman", tex, 0, 0, true);
		go->AddComponent(comp);
		comp = std::make_shared<dae::CollisionComponent>(16.f, 16.f, false, scene.GetName());
		go->AddComponent(comp);
		std::shared_ptr<dae::Component> pacman = std::make_shared<dae::PacMan>(std::dynamic_pointer_cast<dae::Score>(score), std::dynamic_pointer_cast<dae::Lives>(lives), 0.5f);
		go->AddComponent(pacman);
		go->SetPosition(300, 100);
		scene.Add(go);

		//Add score 2
		go = std::make_shared<dae::GameObject>();
		comp = std::make_shared<dae::RenderComponent>();
		go->AddComponent(comp);
		comp = std::make_shared<dae::TextComponent>("REEEEEEE", font);
		go->AddComponent(comp);
		score = std::make_shared<dae::Score>();
		go->AddComponent(score);
		go->SetPosition(10, 15);
		scene.Add(go);

		//Moving Pacman 2
		go = std::make_shared<dae::GameObject>();
		command = std::make_shared<dae::MoveCommand>(speed, dae::Direction::UP, go);
		comp = std::make_shared<dae::InputComponent>(command, dae::InputType::DOWN, 0, dae::ControllerButton::LStickUp);
		go->AddComponent(comp);
		command = std::make_shared<dae::MoveCommand>(speed, dae::Direction::DOWN, go);
		comp = std::make_shared<dae::InputComponent>(command, dae::InputType::DOWN, 0, dae::ControllerButton::LStickDown);
		go->AddComponent(comp);
		command = std::make_shared<dae::MoveCommand>(speed, dae::Direction::RIGHT, go);
		comp = std::make_shared<dae::InputComponent>(command, dae::InputType::DOWN, 0, dae::ControllerButton::LStickRight);
		go->AddComponent(comp);
		command = std::make_shared<dae::MoveCommand>(speed, dae::Direction::LEFT, go);
		comp = std::make_shared<dae::InputComponent>(command, dae::InputType::DOWN, 0, dae::ControllerButton::LStickLeft);
		go->AddComponent(comp);
		comp = std::make_shared<dae::RenderComponent>();
		tex = dae::ResourceManager::GetInstance().LoadTexture("Pacwoman.png");
		(std::dynamic_pointer_cast<dae::RenderComponent>(comp))->AddTexture("Pacman", tex, 0, 0, true);
		go->AddComponent(comp);
		comp = std::make_shared<dae::CollisionComponent>(16.f, 16.f, false, scene.GetName());
		go->AddComponent(comp);
		std::shared_ptr<dae::Component> pacwoman = std::make_shared<dae::PacMan>(std::dynamic_pointer_cast<dae::Score>(score), std::dynamic_pointer_cast<dae::Lives>(lives), 0.5f);
		go->AddComponent(pacwoman);
		go->SetPosition(300, 390);
		scene.Add(go);

		//Ghosts
		SpawnGhost(500, 70, scene, std::dynamic_pointer_cast<dae::PacMan>(pacman), powerUp, std::dynamic_pointer_cast<dae::PacMan>(pacwoman));
		SpawnGhost(100, 70, scene, std::dynamic_pointer_cast<dae::PacMan>(pacman), powerUp, std::dynamic_pointer_cast<dae::PacMan>(pacwoman));
		SpawnGhost(100, 420, scene, std::dynamic_pointer_cast<dae::PacMan>(pacman), powerUp, std::dynamic_pointer_cast<dae::PacMan>(pacwoman));
		SpawnGhost(500, 420, scene, std::dynamic_pointer_cast<dae::PacMan>(pacman), powerUp, std::dynamic_pointer_cast<dae::PacMan>(pacwoman));

		//Add FPS
		go = std::make_shared<dae::GameObject>();
		comp = std::make_shared<dae::RenderComponent>();
		go->AddComponent(comp);
		font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
		comp = std::make_shared<dae::TextComponent>("If you can read this I fucked up", font);
		go->AddComponent(comp);
		comp = std::make_shared<dae::FPSDisplay>();
		go->AddComponent(comp);
		go->SetPosition(550, 10);
		scene.Add(go);
	}

	//2 player scene Versus
	{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Versus");

	//Add PowerUp thread
	auto go = std::make_shared<dae::GameObject>();
	std::shared_ptr<dae::Component>comp = std::make_shared<dae::ThreadComponent>(0, scene.GetName());
	go->AddComponent(comp);
	auto powerUp = std::make_shared<dae::PowerUpPill>(5.f);
	comp = std::dynamic_pointer_cast<dae::Component>(powerUp);
	go->AddComponent(comp);
	scene.Add(go);

	//Add some tiles for testing
	LoadLevel("../Data/Level.txt", scene, powerUp);

	//Add score 1
	go = std::make_shared<dae::GameObject>();
	comp = std::make_shared<dae::RenderComponent>();
	go->AddComponent(comp);
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	comp = std::make_shared<dae::TextComponent>("REEEEEEE", font);
	go->AddComponent(comp);
	std::shared_ptr<dae::Component> score = std::make_shared<dae::Score>();
	go->AddComponent(score);
	go->SetPosition(10, 10);
	scene.Add(go);

	//Add Lives display 1
	go = std::make_shared<dae::GameObject>();
	comp = std::make_shared<dae::RenderComponent>();
	go->AddComponent(comp);
	comp = std::make_shared<dae::TextComponent>("DefaultString", font);
	go->AddComponent(comp);
	std::shared_ptr<dae::Component> lives = std::make_shared<dae::Lives>();
	go->AddComponent(lives);
	go->SetPosition(100, 10);
	scene.Add(go);

	//Moving Pacman 1
	go = std::make_shared<dae::GameObject>();
	float speed = 200.f;
	std::shared_ptr<dae::Command> command = std::make_shared<dae::MoveCommand>(speed, dae::Direction::UP, go);
	comp = std::make_shared<dae::InputComponent>(command, dae::InputType::DOWN, SDLK_UP, dae::ControllerButton::NONE);
	go->AddComponent(comp);
	command = std::make_shared<dae::MoveCommand>(speed, dae::Direction::DOWN, go);
	comp = std::make_shared<dae::InputComponent>(command, dae::InputType::DOWN, SDLK_DOWN, dae::ControllerButton::NONE);
	go->AddComponent(comp);
	command = std::make_shared<dae::MoveCommand>(speed, dae::Direction::RIGHT, go);
	comp = std::make_shared<dae::InputComponent>(command, dae::InputType::DOWN, SDLK_RIGHT, dae::ControllerButton::NONE);
	go->AddComponent(comp);
	command = std::make_shared<dae::MoveCommand>(speed, dae::Direction::LEFT, go);
	comp = std::make_shared<dae::InputComponent>(command, dae::InputType::DOWN, SDLK_LEFT, dae::ControllerButton::NONE);
	go->AddComponent(comp);
	comp = std::make_shared<dae::RenderComponent>();
	auto tex = dae::ResourceManager::GetInstance().LoadTexture("Pacman.png");
	(std::dynamic_pointer_cast<dae::RenderComponent>(comp))->AddTexture("Pacman", tex, 0, 0, true);
	go->AddComponent(comp);
	comp = std::make_shared<dae::CollisionComponent>(16.f, 16.f, false, scene.GetName());
	go->AddComponent(comp);
	std::shared_ptr<dae::Component> pacman = std::make_shared<dae::PacMan>(std::dynamic_pointer_cast<dae::Score>(score), std::dynamic_pointer_cast<dae::Lives>(lives), 0.5f);
	go->AddComponent(pacman);
	go->SetPosition(300, 100);
	scene.Add(go);

	//Player Ghost
	go = std::make_shared<dae::GameObject>();
	command = std::make_shared<dae::MoveCommand>(speed, dae::Direction::UP, go);
	comp = std::make_shared<dae::InputComponent>(command, dae::InputType::DOWN, 0, dae::ControllerButton::LStickUp);
	go->AddComponent(comp);
	command = std::make_shared<dae::MoveCommand>(speed, dae::Direction::DOWN, go);
	comp = std::make_shared<dae::InputComponent>(command, dae::InputType::DOWN, 0, dae::ControllerButton::LStickDown);
	go->AddComponent(comp);
	command = std::make_shared<dae::MoveCommand>(speed, dae::Direction::RIGHT, go);
	comp = std::make_shared<dae::InputComponent>(command, dae::InputType::DOWN, 0, dae::ControllerButton::LStickRight);
	go->AddComponent(comp);
	command = std::make_shared<dae::MoveCommand>(speed, dae::Direction::LEFT, go);
	comp = std::make_shared<dae::InputComponent>(command, dae::InputType::DOWN, 0, dae::ControllerButton::LStickLeft);
	go->AddComponent(comp);
	comp = std::make_shared<dae::RenderComponent>();
	tex = dae::ResourceManager::GetInstance().LoadTexture("Ghost.png");
	(std::dynamic_pointer_cast<dae::RenderComponent>(comp))->AddTexture("Ghost", tex, 0, 0, true);
	tex = dae::ResourceManager::GetInstance().LoadTexture("ScaredGhost.png");
	(std::dynamic_pointer_cast<dae::RenderComponent>(comp))->AddTexture("ScaredGhost", tex, 0, 0, true);
	go->AddComponent(comp);
	comp = std::make_shared<dae::CollisionComponent>(16.f, 16.f, false, scene.GetName());
	go->AddComponent(comp);
	comp = std::make_shared<dae::PlayerGhost>(std::dynamic_pointer_cast<dae::PacMan>(pacman));
	powerUp->AddGhost(std::dynamic_pointer_cast<dae::PlayerGhost>(comp));
	go->AddComponent(comp);
	go->SetPosition(300, 390);
	scene.Add(go);

	//Add FPS
	go = std::make_shared<dae::GameObject>();
	comp = std::make_shared<dae::RenderComponent>();
	go->AddComponent(comp);
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	comp = std::make_shared<dae::TextComponent>("If you can read this I fucked up", font);
	go->AddComponent(comp);
	comp = std::make_shared<dae::FPSDisplay>();
	go->AddComponent(comp);
	go->SetPosition(550, 10);
	scene.Add(go);
	}

	//Menu scene
	{
		auto& scene = dae::SceneManager::GetInstance().CreateScene("Menu");
		auto go = std::make_shared<dae::GameObject>();
		auto tex = dae::ResourceManager::GetInstance().LoadTexture("background.jpg");
		std::shared_ptr<dae::Component> comp = std::make_shared<dae::RenderComponent>();
		(std::dynamic_pointer_cast<dae::RenderComponent>(comp))->AddTexture("Background", tex, 0, 0, false);
		go->AddComponent(comp);
		std::shared_ptr<dae::Command> com = std::make_shared<dae::SceneSwapCommand>(dae::SceneType::ONE_PLAYER);
		comp = std::make_shared<dae::InputComponent>(com, dae::InputType::RELEASED, SDLK_1);
		go->AddComponent(comp);
		com = std::make_shared<dae::SceneSwapCommand>(dae::SceneType::TWO_PLAYER);
		comp = std::make_shared<dae::InputComponent>(com,dae::InputType::RELEASED, SDLK_2);
		go->AddComponent(comp);
		com = std::make_shared<dae::SceneSwapCommand>(dae::SceneType::VERSUS);
		comp = std::make_shared<dae::InputComponent>(com, dae::InputType::RELEASED, SDLK_3);
		go->AddComponent(comp);
		scene.Add(go);

		go = std::make_shared<dae::GameObject>();
		comp = std::make_shared<dae::RenderComponent>();
		go->AddComponent(comp);
		auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
		comp = std::make_shared<dae::TextComponent>("Mode selection", font);
		go->AddComponent(comp);
		go->SetPosition(160, 10);
		scene.Add(go);

		go = std::make_shared<dae::GameObject>();
		comp = std::make_shared<dae::RenderComponent>();
		go->AddComponent(comp);
		comp = std::make_shared<dae::TextComponent>("1 : SinglePlayer", font);
		go->AddComponent(comp);
		go->SetPosition(200, 80);
		scene.Add(go);

		go = std::make_shared<dae::GameObject>();
		comp = std::make_shared<dae::RenderComponent>();
		go->AddComponent(comp);
		comp = std::make_shared<dae::TextComponent>("2 : Co-op", font);
		go->AddComponent(comp);
		go->SetPosition(200, 110);
		scene.Add(go);

		go = std::make_shared<dae::GameObject>();
		comp = std::make_shared<dae::RenderComponent>();
		go->AddComponent(comp);
		comp = std::make_shared<dae::TextComponent>("3 : Versus", font);
		go->AddComponent(comp);
		go->SetPosition(200, 140);
		scene.Add(go);
	}

	dae::SceneManager::GetInstance().SetActiveScene("Menu");
}

void Game::LoadLevel(std::string path, dae::Scene& scene, std::shared_ptr<dae::PowerUpPill> powerUp)
{
	std::ifstream file{ path };
	std::string s, f = "";

	int width = 0, height = 0, size = 0, count = 0;

	std::getline(file, s);
	s += ' ';
	for(char c : s)
	{
		if(c != ' ')
		{
			f += c;
		}
		else
		{
			switch(count)
			{
			case 0:
				width = std::stoi(f);
				break;
			case 1:
				height = std::stoi(f);
				break;
			case 2:
				size = std::stoi(f);
				break;
			}
			f = "";
			count++;
		}
	}

	for(int i = 0; i < height;i++)
	{
		std::getline(file, s);
		for(int j = 0; j < width; j++)
		{
			switch(s.c_str()[j])
			{
			case '0':
			{
				auto go = std::make_shared<dae::GameObject>();
				std::shared_ptr<dae::Component> comp = std::make_shared<dae::RenderComponent>();
				auto tex = dae::ResourceManager::GetInstance().LoadTexture("Pill.png");
				(std::dynamic_pointer_cast<dae::RenderComponent>(comp))->AddTexture("Tile", tex, 0, 0, true);
				go->AddComponent(comp);
				comp = std::make_shared<dae::CollisionComponent>(32.f,32.f,true,scene.GetName());
				std::shared_ptr<dae::TriggerCommand> com = std::make_shared<dae::PillCommand>(1,go);
				(std::dynamic_pointer_cast<dae::CollisionComponent>(comp))->SetTrigger(com,true);
				go->AddComponent(comp);
				go->SetPosition(float((j*size)), float((i + 1)*size));
				scene.Add(go);
				break;
			}
			case '1':
			{
				auto go = std::make_shared<dae::GameObject>();
				std::shared_ptr<dae::Component> comp = std::make_shared<dae::RenderComponent>();
				auto tex = dae::ResourceManager::GetInstance().LoadTexture("Tile.png");
				(std::dynamic_pointer_cast<dae::RenderComponent>(comp))->AddTexture("Tile", tex, 0, 0, true);
				go->AddComponent(comp);
				comp = std::make_shared<dae::CollisionComponent>(32.f, 32.f, true,scene.GetName());
				go->AddComponent(comp);
				go->SetPosition(float((j*size)), float((i + 1)*size));
				scene.Add(go);
				break;
			}
			case '2':
			{
				auto go = std::make_shared<dae::GameObject>();
				std::shared_ptr<dae::Component> comp = std::make_shared<dae::RenderComponent>();
				auto tex = dae::ResourceManager::GetInstance().LoadTexture("PowerUpPill.png");
				(std::dynamic_pointer_cast<dae::RenderComponent>(comp))->AddTexture("Tile",tex,0,0,true);
				go->AddComponent(comp);
				comp = std::make_shared<dae::CollisionComponent>(32.f, 32.f, true,scene.GetName());
				std::shared_ptr<dae::TriggerCommand> com = std::make_shared<dae::PowerUpPillCommand>(powerUp,go);
				(std::dynamic_pointer_cast<dae::CollisionComponent>(comp))->SetTrigger(com, true);
				go->AddComponent(comp);
				go->SetPosition(float((j*size)), float((i + 1)*size));
				scene.Add(go);
				break;
			}
			}
		}
	}
}

void Game::SpawnGhost(float x, float y, dae::Scene& scene, std::shared_ptr<dae::PacMan> pacman, std::shared_ptr<dae::PowerUpPill> powerUp,std::shared_ptr<dae::PacMan> pacwoman)
{
	srand(int(time(NULL)));

	auto go = std::make_shared<dae::GameObject>();
	float speed = 200.f;
	std::shared_ptr<dae::Component> comp = std::make_shared<dae::CollisionComponent>(16.f, 16.f, false,scene.GetName());
	go->AddComponent(comp);
	comp = std::make_shared<dae::RenderComponent>();
	auto tex = dae::ResourceManager::GetInstance().LoadTexture("Ghost.png");
	(std::dynamic_pointer_cast<dae::RenderComponent>(comp))->AddTexture("Ghost", tex, 0, 0, true);
	tex = dae::ResourceManager::GetInstance().LoadTexture("ScaredGhost.png");
	(std::dynamic_pointer_cast<dae::RenderComponent>(comp))->AddTexture("ScaredGhost", tex, 0, 0, true);
	go->AddComponent(comp);
	comp = std::make_shared<dae::ThreadComponent>(rand() % 9999999,scene.GetName());
	go->AddComponent(comp);
	comp = std::make_shared<dae::Ghost>(speed, pacman, pacwoman);
	powerUp->AddGhost(std::dynamic_pointer_cast<dae::Ghost>(comp));
	go->AddComponent(comp);
	go->SetPosition(x, y);
	scene.Add(go);
}
