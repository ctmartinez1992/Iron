#ifndef Demo_Main_Game_H_
#define Demo_Main_Game_H_

#include "Iron.h"
#include "Sprite.h"

enum class GameState {
	PLAY = 0,
	EXIT
};

class MainGame {
private:
	SDL_Window* w;
	GameState state;
	Sprite sprite;
	int sW;
	int sH;

public:
	MainGame();
	~MainGame();

	void initSystems();
	void input();
	void loop();
	void render();
	void run();
};

#endif
