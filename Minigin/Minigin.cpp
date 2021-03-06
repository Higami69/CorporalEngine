#include "MiniginPCH.h"
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#pragma comment(lib,"xinput.lib")
#include "SDL.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"

#include "Scene.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "TimeManager.h"
#include "RenderComponent.h"
#include "Game.h"
#include "CollisionManager.h"
#include "ThreadManager.h"

const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps

void Initialize();
void LoadGame();
void Cleanup();

std::shared_ptr<dae::GameObject> to; //Temp code until Scene and SCeneManager have been rewritten 

#pragma warning( push )  
#pragma warning( disable : 4100 )  
int main(int argc, char* argv[]) {
#pragma warning( pop )

	Initialize();

	// tell the resource manager where he can find the game data
	dae::ResourceManager::GetInstance().Init("../Data/");

	//LoadGame();
	Game::LoadGame();
	dae::SceneManager::GetInstance().Initialize();

	{
		auto t = std::chrono::high_resolution_clock::now();
		auto& renderer = dae::Renderer::GetInstance();
		auto& sceneManager = dae::SceneManager::GetInstance();
		auto& input = dae::InputManager::GetInstance();
		auto& timeManager = dae::TimeManager::GetInstance();
		auto& collisionManager = dae::CollisionManager::GetInstance();
		auto& threadManager = dae::ThreadManager::GetInstance();

		bool doContinue = true;
		while(doContinue) 
		{
			try
			{
				//Check which inputs have been received
				doContinue = input.ProcessInput();

				//Update 
				sceneManager.Update();
				sceneManager.LateUpdate();
				collisionManager.Update();
				timeManager.Update();
				threadManager.Update();

				//Render
				renderer.Render();

				//Cap FPS
				t += std::chrono::milliseconds(msPerFrame);
				std::this_thread::sleep_until(t);
			}
			catch(std::exception e)
			{
				std::cout << "Exception: " << e.what();
			}
			catch(...)
			{
				std::cout << "Error! Unknown exception!";
				return -1;
			}
		}
	}

	dae::ThreadManager::GetInstance().CloseThreads(dae::SceneManager::GetInstance().GetActiveSceneName());
	Cleanup();
    return 0;
}

SDL_Window* window;

void Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::stringstream ss; ss << "SDL_Init Error: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,                    
		480,                    
		SDL_WINDOW_OPENGL       
	);
	if (window == nullptr) {
		std::stringstream ss; ss << "SDL_CreateWindow Error: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}

	dae::Renderer::GetInstance().Init(window);
}

void LoadGame()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	
	auto go = std::make_shared<dae::GameObject>();
	std::shared_ptr<dae::Component> tex = std::make_shared<dae::RenderComponent>();
	auto t = dae::ResourceManager::GetInstance().LoadTexture("background.jpg");
	(std::dynamic_pointer_cast<dae::RenderComponent>(tex))->AddTexture("Background", t, 0, 0, false);
	go->AddComponent(tex);
	t = dae::ResourceManager::GetInstance().LoadTexture("logo.png");
	(std::dynamic_pointer_cast<dae::RenderComponent>(tex))->AddTexture("Logo", t, 216, 180, false);
	go->AddComponent(tex);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<dae::GameObject>();
	std::shared_ptr<dae::Component> tc = std::make_shared<dae::RenderComponent>();
	go->AddComponent(tc);
	tc = std::make_shared<dae::TextComponent>("Test", font);
	go->AddComponent(tc);
	go->SetPosition(20, 20);
	scene.Add(go);
}

void Cleanup()
{
	dae::Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	SDL_Quit();
}

