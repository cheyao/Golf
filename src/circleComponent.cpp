#include "circleComponent.hpp"

#include "actor.hpp"
#include "common.hpp"
#include "component.hpp"

CircleComponent::CircleComponent(class Actor* owner) : Component(owner) {}

float CircleComponent::getRadius() const {
	return mRadius * mOwner->getScale();
}

const Vector2& CircleComponent::getCenter() const {
	return mOwner->getPosition();
}

bool CircleComponent::intersect(const CircleComponent& a,
				const CircleComponent& b) {
	float distance = (a.getCenter() - b.getCenter()).lengthSquared();

	float radius = (a.getRadius() + b.getRadius());
	radius *= radius;

	return distance <= radius;
}

bool CircleComponent::intersect(const Vector2& vec, const CircleComponent& circle) { return intersect(circle, vec); }
bool CircleComponent::intersect(const CircleComponent& circle, const Vector2& vec) {
	float distance = (circle.getCenter() - vec).lengthSquared();

	float radius = circle.getRadius();
	radius *= radius;

	return distance <= radius;
}

