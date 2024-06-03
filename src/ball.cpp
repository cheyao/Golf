#include "ball.hpp"

#include <algorithm>
#include <string>
#include <vector>

#include "circleComponent.hpp"
#include "common.hpp"
#include "flingComponent.hpp"
#include "game.hpp"
#include "hole.hpp"
#include "movementComponent.hpp"
#include "spriteComponent.hpp"

Ball::Ball(Game* game) : Actor(game) {
	SpriteComponent* ballSprite = new SpriteComponent(this);
	ballSprite->setTexture(game->getTexture("assets/Ball.png"));

	MovementComponent* ballMouvement = new MovementComponent(this);
	ballMouvement->setAngularSpeed(0.f);
	ballMouvement->setForwardSpeed(5.f);

	mCircle = new CircleComponent(this);
	mCircle->setRadius(50.f);

	new FlingComponent(this);

	setForward(Vector2::normalize(Vector2(0.f, 0.f)));
}

void Ball::updateActor(float delta) {
	(void)delta;

	std::vector<Hole*>& holes = getGame()->getHoles();

	auto iter =
	    std::find_if(holes.begin(), holes.end(), [=](const Hole* hole) {
		    return CircleComponent::intersect(*mCircle,
						      *(hole->getCircle()));
	    });
	if (iter != holes.end()) {
		this->setState(STATE_DEAD);
		(*iter)->setState(STATE_DEAD);
	}
}

