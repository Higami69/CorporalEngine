#include "MiniginPCH.h"
#include "InputManager.h"
#include "InputComponent.h"
#include <SDL.h>


bool dae::InputManager::ProcessInput()
{
	prevState = currentState;
	XInputGetState(0, &currentState);

	if (SDL_PollEvent(&currentEvent) != 0)
	{
		if (currentEvent.type == SDL_QUIT) return false;

		return true;
	}
	return true;
}


bool dae::InputManager::IsDown(ControllerButton button) const
{
	switch(button)
	{
	case ControllerButton::ButtonA:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::LStickDown:
		return (currentState.Gamepad.sThumbLY / 32768) < 0.0f;
	case ControllerButton::LStickLeft:
		return (currentState.Gamepad.sThumbLX / 32768) < 0.0f;
	case ControllerButton::LStickRight:
		return (currentState.Gamepad.sThumbLX / 32767) > 0.0f;
	case ControllerButton::LStickUp:
		return (currentState.Gamepad.sThumbLY / 32767) > 0.0f;
	}
	return false;

}

bool dae::InputManager::IsDown(SDL_Keycode keyCode) const
{
	(keyCode);
	if (currentEvent.type == SDL_KEYDOWN && currentEvent.key.keysym.sym == keyCode) return true;
	return false;
}

bool dae::InputManager::IsReleased(ControllerButton button) const
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		return (prevState.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(currentState.Gamepad.wButtons & XINPUT_GAMEPAD_A);
	case ControllerButton::LStickDown:
		return ((prevState.Gamepad.sThumbLY / 32768) < 0.0f) && ((currentState.Gamepad.sThumbLY / 32768) > 0.0f);
	case ControllerButton::LStickLeft:
		return ((prevState.Gamepad.sThumbLX / 32768) < 0.0f) && ((currentState.Gamepad.sThumbLX / 32768) > 0.0f);
	case ControllerButton::LStickRight:
		return ((prevState.Gamepad.sThumbLX / 32767) > 0.0f) && ((currentState.Gamepad.sThumbLX / 32767) < 0.0f);
	case ControllerButton::LStickUp:
		return ((prevState.Gamepad.sThumbLY / 32767) > 0.0f) && ((currentState.Gamepad.sThumbLY / 32767) < 0.0f);
	}
	return false;
}

bool dae::InputManager::IsReleased(SDL_Keycode keyCode) const
{
	if (keyCode == currentEvent.key.keysym.sym && currentEvent.type == SDL_KEYUP) return true;
	return false;
}
