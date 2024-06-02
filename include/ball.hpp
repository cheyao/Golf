#ifndef BALL_H
#define BALL_H
#pragma once

#include "actor.hpp"

class Ball : public Actor {
       public:
	explicit Ball(class Game* game);

	void updateActor(float delta) override;

	class CircleComponent* getCircle() const { return mCircle; }

       private:
	static const int mRadius = 50;
	class CircleComponent* mCircle;
};

#endif
