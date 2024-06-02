#ifndef CIRCLE_COMPONENT_HPP
#define CIRCLE_COMPONENT_HPP
#pragma once

#include "common.hpp"
#include "component.hpp"

class CircleComponent : public Component {
       public:
	explicit CircleComponent(class Actor* owner);

	void setRadius(float radius) { mRadius = radius; }
	float getRadius() const;

	const Vector2& getCenter() const;

	static bool intersect(const CircleComponent& a, const CircleComponent& b);
	static bool intersect(const CircleComponent& circle, const Vector2& vec);
	static bool intersect(const Vector2& vec, const CircleComponent& circle);

       private:
	float mRadius;
};


#endif	// CIRCLE_COMPONENT_HPP
