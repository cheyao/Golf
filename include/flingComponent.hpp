#pragma once

#include <SDL3/SDL.h>

#include "common.hpp"
#include "spriteComponent.hpp"

class FlingComponent : public SpriteComponent {
       public:
	explicit FlingComponent(class Actor* owner);

	void input() override;
	void draw(SDL_Renderer* renderer) override;

       private:
	const static constexpr float mMaxLength = 300.f;
	bool mSelected;
	// The point where the mouse was clicked
	class Vector2 mOrigin;
};

