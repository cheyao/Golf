#pragma once

#include "actor.hpp"

class Hole : public Actor {
       public:
	explicit Hole(class Game* game);
	~Hole() override;

	class CircleComponent* getCircle() const { return mCircle; }

	// No copy
	Hole(const Hole&) = delete;
	Hole& operator=(const Hole& x) = delete;

       private:
	class CircleComponent* mCircle;
};

