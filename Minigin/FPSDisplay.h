#pragma once
#include "Component.h"
#include <memory>

namespace dae
{
	class TextComponent;

	class FPSDisplay : public Component
	{
	public:
		FPSDisplay();

		void Initialize() override;
		void Update() override;
		void Render() const override;

	private:
		std::weak_ptr<TextComponent> m_pText;
	};
}