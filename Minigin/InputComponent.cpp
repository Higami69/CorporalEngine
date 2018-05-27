#include "MiniginPCH.h"
#include "InputComponent.h"
#include "Command.h"

dae::InputComponent::InputComponent(std::shared_ptr<Command> command, InputType type, SDL_Keycode key, ControllerButton button)
	:Component(false)
	,m_Command(command)
	,m_KeyCode(key)
	,m_Button(button)
	,m_Type(type)
{
}

void dae::InputComponent::Initialize()
{
}

void dae::InputComponent::Update()
{
	auto input = &InputManager::GetInstance();

	switch (m_Type)
	{
	case InputType::DOWN:
		if (input->IsDown(m_KeyCode) || input->IsDown(m_Button)) m_Command->Execute();
		break;
	case InputType::RELEASED:
		if (input->IsReleased(m_KeyCode) || input->IsReleased(m_Button)) m_Command->Execute();
		break;
	}
}

void dae::InputComponent::Render() const
{
}
