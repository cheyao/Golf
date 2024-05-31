#ifndef GAME_HPP
#define GAME_HPP
#include <list>
#include <unordered_map>
#pragma once

#include <SDL3/SDL.h>

#include <vector>

#include "common.hpp"

class Game {
       public:
	Game();
	~Game();

	int init();
	int iterate();
	int event(const SDL_Event& event);

	void addActor(class Actor* actor);
	void removeActor(class Actor* actor);

	void addSprite(class SpriteComponent* sprite);
	void removeSprite(class SpriteComponent* sprite);

	// No copy
	Game(Game const&) = delete;
	void operator=(Game const& x) = delete;

       private:
	void input();
	void update();
	void draw();
	void gui();

	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;

	std::vector<class SpriteComponent*> mSprites;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint64 mTicks;
	Uint64 mUpdates;

	bool mUpdatingActors;

	int mWindowWidth, mWindowHeight;

	std::unordered_map<int, bool> mKeyboard;
	std::list<TouchEvent> mTouchEvents;
};

#endif	// GAME_HPP
