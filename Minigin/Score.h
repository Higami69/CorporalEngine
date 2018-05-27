#pragma once
#include "Component.h"
#include <memory>

namespace dae
{
	class TextComponent;

	class Score : public Component
	{
	public:
		Score();

		void Initialize() override;
		void Update() override;
		void Render() const override;

		void AddScore(int score);
	private:
		std::weak_ptr<TextComponent> m_pText;
		int m_Score;
	};
}