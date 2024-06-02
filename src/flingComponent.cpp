#include "flingComponent.hpp"

#include "actor.hpp"
#include "ball.hpp"
#include "circleComponent.hpp"
#include "component.hpp"
#include "game.hpp"
#include "spriteComponent.hpp"

FlingComponent::FlingComponent(Actor* owner)
    : SpriteComponent(owner, 101), mSelected(false) {}

void FlingComponent::input() {
	Ball* ball = dynamic_cast<Ball*>(mOwner);
	if (ball == nullptr) {
		return;
	}

	/*
	for (auto touch : mOwner->getGame()->getTouchEvents()) {
	if (CircleComponent::intersect(ball->getCircle(), touch) {
			}
	}*/
}

void FlingComponent::draw(SDL_Renderer* renderer) {
	if (!mSelected) {
		return;
	}

	Ball* ball = dynamic_cast<Ball*>(mOwner);
	if (ball == nullptr) {
		return;
	}

	Vector2 position = ball->getCircle()->getCenter();
	float radius = ball->getCircle()->getRadius();

	SDL_RenderLine(renderer, position.x - radius, position.y,
		       position.x + radius, position.y);
}

