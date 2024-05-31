#include "game.hpp"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stddef.h>

#include <algorithm>
#include <iterator>
#include <string>

#ifdef __EMSCRIPTEN__
#include <emscripten/html5.h>

EM_JS(int, browserHeight, (), { return window.innerHeight; });

EM_JS(int, browserWidth, (), { return window.innerWidth; });
#endif

#include "actor.hpp"
#include "common.hpp"
#include "spriteComponent.hpp"

Game::Game()
    : mWindow(nullptr),
      mRenderer(nullptr),
      mUpdatingActors(false),
      mWindowWidth(1024),
      mWindowHeight(768) {}

int Game::init() {
	SDL_Log("Initializing game\n");

	if (SDL_Init(SDL_INIT_VIDEO)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			     "Failed to init SDL: %s\n", SDL_GetError());
		return 1;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			     "Failed to init SDL_image: %s\n", SDL_GetError());
		return 1;
	}

	// Create window and Renderer
#ifdef __EMSCRIPTEN__
	// Hacks for EMSCRIPTEN Full screen
	mWindowWidth = browserWidth();
	mWindowHeight = browserHeight();

	mWindow =
	    SDL_CreateWindow("TileMap", mWindowWidth, mWindowHeight, SDL_WINDOW_RESIZABLE);
#else
	mWindow = SDL_CreateWindow("TileMap", 1024, 768, SDL_WINDOW_RESIZABLE);
#endif
	if (mWindow == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			     "Failed to create window: %s\n", SDL_GetError());
		return 1;
	}

	mRenderer = SDL_CreateRenderer(mWindow, NULL);
	if (mRenderer == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			     "Failed to create renderer: %s", SDL_GetError());
		return 1;
	}

	// Make sure that the widnow can be resized
	SDL_SetRenderLogicalPresentation(mRenderer, 1024, 768,
					 SDL_LOGICAL_PRESENTATION_LETTERBOX,
					 SDL_SCALEMODE_NEAREST);

	mTicks = SDL_GetTicks();

	Actor* background = new Actor(this);
	background->setPosition(Vector2(0.f, 0.f));

	char* basepath = SDL_GetBasePath();
	std::string base;
	if (basepath == NULL) {
		base = "";
	} else {
		base = static_cast<std::string>(basepath);
		SDL_free(basepath);  // We gotta free da pointer UwU
	}

	SDL_Log("Successfully initialized game\n");

	return 0;
}

void Game::input() {
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	mUpdatingActors = true;
	for (auto actor : mActors) {
		actor->input(keystate);
	}
	mUpdatingActors = false;
}

void Game::update() {
	// Hack for web window resizing
#ifdef __EMSCRIPTEN__
	if (browserWidth() != mWindowWidth || browserHeight() != mWindowHeight) {
		mWindowWidth = browserWidth();
		mWindowHeight = browserHeight();

		SDL_SetWindowSize(mWindow, mWindowWidth, mWindowHeight);
	}
#endif

	// Update the game
	float delta = (SDL_GetTicks() - mTicks) / 1000.0f;
	if (delta > 0.05) {
		delta = 0.05;
	}
	mTicks = SDL_GetTicks();

	// Update the Actors
	mUpdatingActors = true;
	for (auto actor : mActors) {
		actor->update(delta);
	}
	mUpdatingActors = false;

	// Append the pending actors
	std::copy(mPendingActors.begin(), mPendingActors.end(),
		  std::back_inserter(mActors));
	mPendingActors.clear();

	// Remove the dead Actors
	std::vector<Actor*> deadActors;
	std::copy_if(mActors.begin(), mActors.end(),
		     std::back_inserter(deadActors), [](const Actor* actor) {
			     return (actor->getState() == Actor::STATE_DEAD);
		     });

	// Delete all the dead actors
	for (auto actor : deadActors) {
		delete actor;
	}
}

void Game::draw() {
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);

	for (auto sprite : mSprites) {
		sprite->draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer);
}

int Game::iterate() {
	// Loop
	input();
	update();
	draw();

	return 0;
}

int Game::event(const SDL_Event& event) {
	switch (event.type) {
		case SDL_EVENT_QUIT:
			return 1;
			break;
		case SDL_EVENT_KEY_DOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				return 1;
			}
			break;
	}

	return 0;
}

void Game::addActor(Actor* actor) {
	if (!mUpdatingActors) {
		mActors.emplace_back(actor);
	} else {
		mPendingActors.emplace_back(actor);
	}
}

void Game::removeActor(Actor* actor) {
	auto iter =
	    std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end()) {
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// Is it in actors?
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end()) {
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::addSprite(SpriteComponent* sprite) {
	int drawOrder = sprite->getDrawOrder();
	auto iter = mSprites.begin();

	for (; iter != mSprites.end(); ++iter) {
		if (drawOrder < (*iter)->getDrawOrder()) {
			break;
		}
	}

	mSprites.insert(iter, sprite);
}
void Game::removeSprite(SpriteComponent* sprite) {
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	if (iter != mSprites.end()) {
		mSprites.erase(iter);
	}
}

Game::~Game() {
	SDL_Log("Quitting game\n");

	while (!mActors.empty()) {
		delete mActors.back();
	}

	while (!mPendingActors.empty()) {
		delete mActors.back();
	}

	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	IMG_Quit();
	SDL_Quit();
}
