#pragma once

#include "actor.hpp"

class Ball : public Actor {
       public:
	explicit Ball(class Game* game);

	void updateActor(float delta) override;

	class CircleComponent* getCircle() const { return mCircle; }

	// No copy
	Ball(const Ball&) = delete;
	Ball& operator=(const Ball& x) = delete;

       private:
	static const int mRadius = 50;
	class CircleComponent* mCircle;
};

