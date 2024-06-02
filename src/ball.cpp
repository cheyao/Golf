#include "ball.hpp"

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
	(void) delta;

	for (auto hole : getGame()->getHoles()) {
		if (CircleComponent::intersect(*(hole->getCircle()), *mCircle)) {
			this->setState(STATE_DEAD);
			hole->setState(STATE_DEAD);
			break;
		}
	}
}

