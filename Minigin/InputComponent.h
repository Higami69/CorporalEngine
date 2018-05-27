#pragma once
#include "Component.h"
#include <SDL.h>
#include "InputManager.h"

namespace dae
{
	class Command;

	enum class InputType
	{
		RELEASED,
		DOWN
	};

	class InputComponent : public Component
	{
	public:
		explicit InputComponent(std::shared_ptr<Command> command, InputType type, SDL_Keycode key = 0, ControllerButton button = ControllerButton::NONE);

		void Initialize() override;
		void Update() override;
		void Render() const override;

	private:
		std::shared_ptr<Command> m_Command;
		SDL_Keycode m_KeyCode;
		ControllerButton m_Button;
		InputType m_Type;
	};
}
