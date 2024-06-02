#include "hole.hpp"

#include "actor.hpp"
#include "circleComponent.hpp"
#include "game.hpp"
#include "spriteComponent.hpp"

Hole::Hole(Game* game) : Actor(game) {
	game->addHole(this);

	SpriteComponent* holeSprite = new SpriteComponent(this, 90);
	holeSprite->setTexture(game->getTexture("assets/Hole.png"));

	mCircle = new CircleComponent(this);
	mCircle->setRadius(50.f);
}

Hole::~Hole() {
	getGame()->removeHole(this);
}

