#pragma once

#include <SDL3/SDL.h>

#include "spriteComponent.hpp"

class FlingComponent : SpriteComponent {
       public:
	explicit FlingComponent(class Actor* owner);

	void input() override;
	void draw(SDL_Renderer* renderer) override;

       private:
	bool mSelected;
};

