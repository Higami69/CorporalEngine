#pragma once
#include "Component.h"

namespace dae
{
	class TextComponent;
	
	class Lives : public Component
	{
	public:
		Lives();

		void Initialize() override;
		void Update() override;
		void Render() const override;

		void SetLives(int lives);
		
	private:
		std::weak_ptr<TextComponent> m_pText;
		int m_Lives;
	};
}
