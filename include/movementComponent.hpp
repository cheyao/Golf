#ifndef MOVEMENT_COMPONENT_HPP
#define MOVEMENT_COMPONENT_HPP
#pragma once

#include "component.hpp"

class MovementComponent : public Component {
       public:
	explicit MovementComponent(class Actor* owner, int updateOrder = 100);

	void update(float delta) override;

	float getAngularSpeed() const { return mAngularSpeed; }
	void setAngularSpeed(float speed) { mAngularSpeed = speed; }
	float getForwardSpeed() const { return mForwardSpeed; }
	void setForwardSpeed(float speed) { mForwardSpeed = speed; }
       private:
	float mAngularSpeed; // RPS
	float mForwardSpeed; // UPS
};

#endif	// MOVEMENT_COMPONENT_HPP
