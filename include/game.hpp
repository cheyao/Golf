#ifndef GAME_HPP
#define GAME_HPP
#pragma once

#include <SDL3/SDL.h>

#include <list>
#include <string>
#include <unordered_map>
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

	void addHole(class Hole* hole);
	void removeHole(class Hole* hole);
	std::vector<class Hole*>& getHoles() { return mHoles; }

	std::unordered_map<int, bool>& getKeyboard() { return mKeyboard; }
	std::list<TouchEvent*>& getTouchEvents() { return mTouchEvents; }

	SDL_Texture* getTexture(const std::string& path) {
		return mTextures[path];
	}

	// No copy
	Game(Game const&) = delete;
	void operator=(Game const& x) = delete;

       private:
	void input();
	void update();
	void gui();
	void draw();
	int loadTexture(const std::string& textureName);

	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;

	std::vector<class SpriteComponent*> mSprites;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint64 mTicks;

	bool mUpdatingActors;

	int mWindowWidth, mWindowHeight;

	std::unordered_map<std::string, SDL_Texture*> mTextures;

	std::unordered_map<int, bool> mKeyboard;
	std::list<struct TouchEvent*> mTouchEvents;

	std::string mBasePath;

	std::vector<class Hole*> mHoles;
};

#endif	// GAME_HPP
