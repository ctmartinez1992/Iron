#pragma once

#include <sdl/SDL.h>
#include <sdl/glew.h>

#include <IronGraphics.h>
#include <GLSLProgram.h>
#include <GLTexture.h>
#include <Sprite.h>
#include <Window.h>
#include <Camera2D.h>

#include <vector>

enum class GameState {PLAY, EXIT};

//Our example game class, just for testing purposes right now
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
    void calculateFPS();

    iron::graphics::Window _window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;

    std::vector <iron::graphics::Sprite*> _sprites;

	iron::graphics::GLSLProgram _colorProgram;
	iron::graphics::Camera2D _camera;

    float _fps;
    float _maxFPS;
    float _frameTime;

    float _time;
};

