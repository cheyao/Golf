#pragma once

#include "component.hpp"

class CircleComponent : public Component {
       public:
	explicit CircleComponent(class Actor* owner);

	void setRadius(float radius) { mRadius = radius; }
	float getRadius() const;

	const class Vector2& getCenter() const;

	static bool intersect(const CircleComponent& a,
			      const CircleComponent& b);
	static bool intersect(const CircleComponent& circle,
			      const class Vector2& vec);
	static bool intersect(const class Vector2& vec,
			      const CircleComponent& circle);

       private:
	float mRadius;
};

