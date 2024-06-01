#include "actor.hpp"

#include <algorithm>

#include "component.hpp"
#include "game.hpp"

Actor::Actor(Game* game)
    : mState(STATE_ALIVE),
      mPosition(Vector2(0.f, 0.f)),
      mForward(Vector2(0.f, 0.f)),
      mScale(1.0f),
      mRotation(0),
      mGame(game) {
	mGame->addActor(this);
}

Actor::~Actor() {
	mGame->removeActor(this);

	while (!mComponents.empty()) {
		delete mComponents.back();
	}
}

void Actor::update(float delta) {
	if (mState == STATE_ALIVE) {
		updateComponents(delta);
		updateActor(delta);
	}
}

void Actor::updateComponents(float delta) {
	for (auto component : mComponents) {
		component->update(delta);
	}
}

void Actor::updateActor(float delta) { (void)delta; }

void Actor::input() {
	if (mState != STATE_ALIVE) {
		return;
	}

	for (auto component : mComponents) {
		component->input();
	}
	actorInput();
}

void Actor::actorInput() {}

void Actor::addComponent(Component* component) {
	int order = component->getUpdateOrder();
	auto iter = mComponents.begin();

	for (; iter != mComponents.end(); ++iter) {
		if (order < (*iter)->getUpdateOrder()) {
			break;
		}
	}

	mComponents.insert(iter, component);
}

void Actor::removeComponent(Component* component) {
	auto iter =
	    std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end()) {
		mComponents.erase(iter);
	}
}

