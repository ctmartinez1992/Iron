#pragma once

#include <SDL.h>
#include <glew.h>

#include "GLSLProgram.h"
#include "GLTexture.h"

#include "Sprite.h"

enum class GameState {PLAY, EXIT};

class MainGame
{
public:
    MainGame();
    ~MainGame();

    void run();

private:
    void initSystems();
    void initShaders();
    void gameLoop();
    void processInput();
    void drawGame();

    SDL_Window* _window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;

    Sprite _sprite;

    GLSLProgram _colorProgram;
    GLTexture _playerTexture;

    float _time;
};

