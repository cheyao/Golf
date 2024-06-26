#include "movementComponent.hpp"

#include "actor.hpp"
#include "common.hpp"
#include "component.hpp"
#include "game.hpp"

MovementComponent::MovementComponent(class Actor* owner, int updateOrder)
    : Component(owner, updateOrder), mAngularSpeed(0.f), mForwardSpeed(100.f) {}

void MovementComponent::update(float delta) {
	if (!maths::nearZero(mAngularSpeed)) {
		float rotation = mOwner->getRotation();
		rotation += mAngularSpeed * delta;
		mOwner->setRotation(rotation);
	}

	Vector2 forwardVec = mOwner->getForward();
	if (!maths::nearZero(forwardVec.length(), 0.1)) {
		Vector2 position = mOwner->getPosition();
		position += mOwner->getForward() * mForwardSpeed * delta;

		// Clip to window bounds
		if (position.x < 50) {
			position.x = 50;
			forwardVec.x = -forwardVec.x;
		}
		if (position.x > 984) {
			position.x = 984;
			forwardVec.x = -forwardVec.x;
		}
		if (position.y < 50) {
			position.y = 50;
			forwardVec.y = -forwardVec.y;
		}
		if (position.y > 718) {
			position.y = 718;
			forwardVec.y = -forwardVec.y;
		}

		mOwner->setPosition(position);

		mOwner->setForward(forwardVec * 0.97f);

		mOwner->getGame()->redraw();
	}
}

