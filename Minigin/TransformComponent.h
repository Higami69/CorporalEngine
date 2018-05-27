#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#include "Component.h"
#pragma warning(pop)

namespace dae
{
	class TransformComponent final : public Component
	{
		glm::vec3 mPosition;
	public:
		TransformComponent();

		void Initialize() override;
		void Update() override;
		void Render() const override;

		const glm::vec3& GetPosition() const { return mPosition; }
		void SetPosition(float x, float y, float z);
	};
}
