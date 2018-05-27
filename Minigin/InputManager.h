#pragma once
#include <XInput.h>
#include "Singleton.h"
#include <SDL.h>

namespace dae
{
	class InputComponent;

	enum class ControllerButton
	{
		ButtonA,
		LStickUp,
		LStickDown,
		LStickLeft,
		LStickRight,
		NONE
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		bool IsDown(ControllerButton button) const;
		bool IsDown(SDL_Keycode keyCode) const;		
		bool IsReleased(ControllerButton button) const;
		bool IsReleased(SDL_Keycode keyCode) const;
	private:
		XINPUT_STATE currentState{}, prevState;
		SDL_Event currentEvent{};
	};

}
