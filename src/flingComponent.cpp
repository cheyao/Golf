#include "flingComponent.hpp"

#include "actor.hpp"
#include "ball.hpp"
#include "circleComponent.hpp"
#include "common.hpp"
#include "game.hpp"
#include "spriteComponent.hpp"

FlingComponent::FlingComponent(Actor* owner)
    : SpriteComponent(owner, 101), mSelected(false), mOrigin() {}

void FlingComponent::input() {
	Ball* ball = dynamic_cast<Ball*>(mOwner);
	if (ball == nullptr) {
		return;
	}

	Mouse& mouse = mOwner->getGame()->getMouse();

	if (!mouse.captured && mouse.type == Mouse::BUTTON_STATE_LEFT &&
	    !mSelected &&
	    maths::nearZero(mOwner->getForward().lengthSquared(),
			    0.1f) &&  // Ball can't be moving
	    CircleComponent::intersect(*(ball->getCircle()), mouse.position)) {
		mSelected = true;
		mouse.captured = true;
		mOrigin = mouse.position;
	}

	if (mSelected && mouse.type == Mouse::BUTTON_STATE_UP) {
		// Released
		mouse.captured = false;
		mSelected = false;

		float length = (mouse.position - mOrigin).length();
		if (length > mMaxLength) {
			length = mMaxLength;  // Not too long
		}
		Vector2 direction = mouse.position - mOrigin;
		direction.normalize();

		mOwner->setForward(direction * length);
	}
}

void FlingComponent::draw(SDL_Renderer* renderer) {
	if (!mSelected) {
		return;
	}

	const Ball* const ball = dynamic_cast<Ball*>(mOwner);
	if (ball == nullptr) {
		return;
	}

	Vector2 mouse = mOwner->getGame()->getMouse().position;
	// float radius = ball->getCircle()->getRadius();
	if ((mouse - mOrigin).lengthSquared() > (mMaxLength * mMaxLength)) {
		Vector2 normalized = mouse - mOrigin;
		normalized.normalize();
		mouse = mOrigin + -(normalized * mMaxLength);
	}

	SDL_RenderLine(renderer, mOrigin.x, mOrigin.y, mouse.x, mouse.y);
}

