#include "MiniginPCH.h"
#include "RenderComponent.h"
#include <SDL.h>
#include "Renderer.h"
#include "Texture2D.h"
#include "GameObject.h"

dae::RenderComponent::RenderComponent()
	:Component(false)
	,m_Sprites()
{
}

void dae::RenderComponent::Initialize()
{
}

void dae::RenderComponent::Update()
{
	for(auto it = m_Sprites.begin();it != m_Sprites.end();++it)
	{
		auto sprite = &it->second;
		if (sprite->movesWithGameObject)
		{
			auto pos = GetGameObject().lock()->GetTransformComponent().GetPosition();
			sprite->x = pos.x;
			sprite->y = pos.y;
		}
	}
}

void dae::RenderComponent::Render() const
{
	for(auto it = m_Sprites.begin(); it != m_Sprites.end(); ++it)
	{
		auto sprite = &it->second;
		if(sprite->isActive) RenderTexture(*sprite->pTexture, sprite->x, sprite->y);
	}
}

void dae::RenderComponent::AddTexture(std::string id, std::shared_ptr<Texture2D> texture, float x, float y, bool moveWithGameObject)
{
	Sprite sprite;
	sprite.x = x;
	sprite.y = y;
	sprite.movesWithGameObject = moveWithGameObject;
	sprite.pTexture = texture;
	m_Sprites[id] = sprite;
}

void dae::RenderComponent::RemoveTexture(std::string id)
{
	m_Sprites.erase(id);
}

void dae::RenderComponent::SetTextureEnabled(std::string id, bool enabled)
{
	m_Sprites[id].isActive = enabled;
}

void dae::RenderComponent::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(Renderer::GetInstance().GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::RenderComponent::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(Renderer::GetInstance().GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}
