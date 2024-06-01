#include "movementComponent.hpp"

#include "common.hpp"
#include "actor.hpp"
#include "component.hpp"

MovementComponent::MovementComponent(class Actor* owner, int updateOrder)
    : Component(owner, updateOrder),
      mAngularSpeed(100.f),
      mForwardSpeed(100.f) {}

void MovementComponent::update(float delta) {
	if (!maths::nearZero(mAngularSpeed)) {
		float rotation = mOwner->getRotation();
		rotation += mAngularSpeed * delta;
		mOwner->setRotation(rotation);
	}

	if (!maths::nearZero(mForwardSpeed)) {
		Vector2 position = mOwner->getPosition();
		position += mOwner->getForward() * mForwardSpeed * delta;
		mOwner->setPosition(position);
	}
}

