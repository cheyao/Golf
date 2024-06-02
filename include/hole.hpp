#ifndef HOLE_HPP
#define HOLE_HPP
#pragma once

#include "actor.hpp"

class Hole : public Actor {
       public:
	explicit Hole(class Game* game);
	~Hole();

	class CircleComponent* getCircle() const { return mCircle; }

       private:
	class CircleComponent* mCircle;
};

#endif	// HOLE_HPP
