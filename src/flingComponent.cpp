#include "flingComponent.hpp"

#include "actor.hpp"
#include "ball.hpp"
#include "circleComponent.hpp"
#include "common.hpp"
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

	Mouse& mouse = mOwner->getGame()->getMouse();

	if (!mouse.captured && mouse.type == Mouse::BUTTON_STATE_LEFT &&
	    !mSelected &&
	    maths::nearZero(mOwner->getForward()
				.lengthSquared()) &&  // Ball can't be moving
	    CircleComponent::intersect(*(ball->getCircle()), mouse.position)) {
		mSelected = true;
		mouse.captured = true;
	}

	if (mSelected && mouse.type == Mouse::BUTTON_STATE_UP) {
		// Released
		mouse.captured = false;
		mSelected = false;

		float length =
		    (mouse.position - mOwner->getPosition()).length();
		Vector2 direction = mouse.position - mOwner->getPosition();
		direction.normalize();

		mOwner->setForward(direction * length);
	}
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
	Vector2 mouse = mOwner->getGame()->getMouse().position;
	// float radius = ball->getCircle()->getRadius();

	if (mSelected) {
		SDL_RenderLine(renderer, position.x, position.y, mouse.x,
			       mouse.y);
	}
}

