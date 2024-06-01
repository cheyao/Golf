#ifndef ACTOR_HPP
#define ACTOR_HPP
#pragma once

#include <vector>

#include "common.hpp"

class Actor {
       public:
	enum State { STATE_ALIVE, STATE_PAUSED, STATE_DEAD };

	explicit Actor(class Game* game);
	virtual ~Actor();

	void update(float delta);
	void updateComponents(float delta);
	virtual void updateActor(float delta);

	void input();
	virtual void actorInput();

	class Game* getGame() { return mGame; }

	const Vector2& getPosition() const { return mPosition; }
	void setPosition(const Vector2& pos) { mPosition = pos; }

	float getScale() const { return mScale; }
	void setScale(float scale) { mScale = scale; }

	float getRotation() const { return mRotation; }
	void setRotation(float rotation) { mRotation = rotation; }

	State getState() const { return mState; }
	void setState(State state) { mState = state; }

	const Vector2& getForward() const { return mForward; }
	void setForward(const Vector2 forward) { mForward = forward; }

	void addComponent(class Component* component);
	void removeComponent(class Component* component);

       private:
	State mState;

	Vector2 mPosition;
	Vector2 mForward;
	float mScale;
	float mRotation; // Radians

	std::vector<class Component*> mComponents;
	class Game* mGame;
};

#endif	// ACTOR_HPP
