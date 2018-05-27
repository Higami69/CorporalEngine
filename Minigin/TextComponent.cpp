#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "RenderComponent.h"

dae::TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font) 
	: mNeedsUpdate(true), mText(text), mFont(font), mTexture(nullptr), Component(false)
{
}

void dae::TextComponent::Initialize()
{
}

void dae::TextComponent::Update()
{
	if (mNeedsUpdate)
	{
		mNeedsUpdate = false;
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(mFont->GetFont(), mText.c_str(), color);
		if (surf == nullptr) {
			std::stringstream ss; ss << "Render text failed: " << SDL_GetError();
			throw std::runtime_error(ss.str().c_str());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) {
			std::stringstream ss; ss << "Create text texture from surface failed: " << SDL_GetError();
			throw std::runtime_error(ss.str().c_str());
		}
		SDL_FreeSurface(surf);
		mTexture = std::make_shared<Texture2D>(texture);
		auto pos = GetGameObject().lock()->GetTransformComponent().GetPosition();
		GetGameObject().lock()->GetComponent<RenderComponent>()->AddTexture("Text", mTexture, pos.x, pos.y, false); //TODO: Give option to make text move
	}
}

void dae::TextComponent::Render() const
{

}

void dae::TextComponent::SetText(const std::string& text)
{
	mText = text;
	mNeedsUpdate = true;
}



