#pragma once
#include "Component.h"
#include <map>
#include "Texture2D.h"

namespace dae
{
	struct Sprite
	{
		Sprite()
			:pTexture(nullptr),
			x(0),
			y(0),
			movesWithGameObject(false),
			isActive(true)
		{
			
		}

		std::shared_ptr<Texture2D> pTexture;
		float x, y;
		bool movesWithGameObject, isActive;
	};

	class RenderComponent final : public Component
	{
	public:
		RenderComponent();

		void Initialize() override;
		void Update() override;
		void Render() const override;

		void AddTexture(std::string id, std::shared_ptr<Texture2D> texture, float x, float y, bool moveWithGameObject);
		void RemoveTexture(std::string id);
		void SetTextureEnabled(std::string id, bool enabled);

	private:
		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		std::map<std::string, Sprite> m_Sprites;
	};
}
