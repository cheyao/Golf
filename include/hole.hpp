#pragma once

#include "actor.hpp"

class Hole : public Actor {
       public:
	explicit Hole(class Game* game);
	~Hole() override;

	class CircleComponent* getCircle() const { return mCircle; }

       private:
	class CircleComponent* mCircle;
};

