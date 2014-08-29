#include "MainGame.h"
#include "Errors.h"

MainGame::MainGame() : w(nullptr), state(GameState::PLAY), time(0), sW(1024), sH(768)
{

}

MainGame::~MainGame() {

}

void MainGame::initSystems() {
	SDL_Init(SDL_INIT_EVERYTHING);

	w = SDL_CreateWindow("Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
		, sW, sH, SDL_WINDOW_OPENGL);
	if (w == nullptr) {
		fatalError("SDL Window could not be created!");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(w);
	if (glContext == nullptr) {
		fatalError("SDL_GL context could not be created!");
	}

	glewExperimental = true;
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("Could not initialize glew!");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	initShaders();
}

void MainGame::initShaders() {
	program.compileShaders("res/shaders/colorShading.vert",
		"res/shaders/colorShading.frag");
	program.addAttribute("vertexPosition");
	program.addAttribute("vertexColor");
	program.linkShaders();
}

void MainGame::input() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
			case SDL_QUIT:
				state = GameState::EXIT;
				break;

			case SDL_MOUSEMOTION:
				std::cout << e.motion.x << " - " << e.motion.y << std::endl;
				break;

			default:
				break;
		}
	}
}

void MainGame::loop() {
	while (state != GameState::EXIT) {
		input();
		time += 0.1f;
		render();
	}
}

void MainGame::render() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	program.use();

	GLuint timeLocation = program.getUniformLocation("time");
	glUniform1f(timeLocation, time);

	sprite.render();

	program.unuse();

	SDL_GL_SwapWindow(w);
}

void MainGame::run() {
	initSystems();
	sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);
	loop();
}