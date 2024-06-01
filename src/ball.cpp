#include "ball.hpp"

#include <string>

#include "common.hpp"
#include "game.hpp"
#include "movementComponent.hpp"
#include "spriteComponent.hpp"

Ball::Ball(Game* game) : Actor(game) {
	setPosition(Vector2(100.f, 100.f));

	SpriteComponent* ballSprite = new SpriteComponent(this);
	ballSprite->setTexture(game->getTexture("assets/Ball.png"));

	MovementComponent* ballMouvement = new MovementComponent(this);
	ballMouvement->setAngularSpeed(0.f);
	ballMouvement->setForwardSpeed(0.f);

	setForward(Vector2::normalize(Vector2(0.f, 0.f)));
}

