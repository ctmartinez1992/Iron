#ifndef Demo_Main_Game_H_
#define Demo_Main_Game_H_

#include "Iron.h"
#include "GLSLProgram.h"
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
	GLSLProgram	program;
	float time;
	int sW;
	int sH;

public:
	MainGame();
	~MainGame();

	void initSystems();
	void initShaders();
	void input();
	void loop();
	void render();
	void run();
};

#endif
