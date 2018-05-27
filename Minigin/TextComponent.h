#pragma once
#include "Component.h"
#include "TransformComponent.h"
#include <memory>
#include <string>

namespace dae
{
	class Font;
	class Texture2D;

	class TextComponent : public Component
	{
	public:
		void Initialize() override;
		void Update() override;
		void Render() const override;

		void SetText(const std::string& text);

		explicit TextComponent(const std::string& text, std::shared_ptr<Font> font);
		~TextComponent() override = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:
		bool mNeedsUpdate;
		std::string mText;
		std::shared_ptr<Font> mFont;
		std::shared_ptr<Texture2D> mTexture;
	};

}
