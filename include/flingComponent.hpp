#ifndef FLING_COMPONENT_HPP
#define FLING_COMPONENT_HPP
#pragma once

#include "spriteComponent.hpp"

class FlingComponent : SpriteComponent {
       public:
	explicit FlingComponent(class Actor* owner);

	void input() override;
	void draw(SDL_Renderer* renderer) override;

       private:
	bool mSelected;
};

#endif

