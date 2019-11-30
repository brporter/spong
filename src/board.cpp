#include "board.h"

#include <cstdlib>
#include <iostream>

#include "resources.h"

Board::Board()
    : _window(nullptr),
      _renderer(nullptr),
      _ball(nullptr),
      _playerOne(),
      _playerTwo(),
      _ballX(INITIAL_BALL_X),
      _ballY(INITIAL_BALL_Y),
      _directionX(0),
      _directionY(0)
{
    SDL_Init(SDL_INIT_VIDEO);

    srand(time(nullptr));

    _directionX = rand() % 10;
    _directionY = rand() % 10;

    SDL_Window* window =
        SDL_CreateWindow("Stupid Pong", SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, BOARD_WIDTH, BOARD_HEIGHT,
                         SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);

    // todo: implement logging
    if (nullptr == window) throw "failed to initialize window";

    _window.reset(window);

    SDL_Renderer* renderer =
        SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED);

    if (nullptr == renderer) throw "failed to initialize renderer";

    _renderer.reset(renderer);

    // todo this is dumb
    std::string blockPath = ResourceManager::getResource(Resources::Block);
    std::string ballPath = ResourceManager::getResource(Resources::Ball);

    SDL_Surface* blockSurface = SDL_LoadBMP(blockPath.c_str());
    SDL_Surface* ballSurface = SDL_LoadBMP(ballPath.c_str());

    SDL_SetColorKey(ballSurface, SDL_TRUE,
                    SDL_MapRGB(ballSurface->format, 0, 255, 0));

    if (nullptr == blockSurface) throw "failed to load block texture";
    if (nullptr == ballSurface) throw "failed to load ball texture";

    SDL_Texture* blockTexture =
        SDL_CreateTextureFromSurface(_renderer.get(), blockSurface);
    SDL_Texture* ballTexture =
        SDL_CreateTextureFromSurface(_renderer.get(), ballSurface);

    if (nullptr == blockTexture || nullptr == ballTexture) {
        std::cerr << SDL_GetError() << std::endl;
    }

    SDL_FreeSurface(blockSurface);
    SDL_FreeSurface(ballSurface);

    _ball.reset(ballTexture);
    _block.reset(blockTexture);
}

Board::~Board()
{
    _renderer.release();
    _window.release();

    SDL_Quit();
}

Player& Board::playerOne() { return _playerOne; }

Player& Board::playerTwo() { return _playerTwo; }

void Board::render()
{
    SDL_RenderClear(_renderer.get());

    // player positions
    SDL_Rect playerOneRect = {50, 0, 30, 100};
    SDL_Rect playerTwoRect = {BOARD_WIDTH - 50, 0, 30, 100};

    playerOneRect.y = _playerOne.position();
    playerTwoRect.y = _playerTwo.position();

    // ball position
    _ballX += _directionX;
    _ballY += _directionY;
    SDL_Rect ballRect = {_ballX, _ballY, 50, 50};

    // top and bottom rectangles
    SDL_Rect topRect = {0, -100, BOARD_WIDTH, 100};
    SDL_Rect botRect = {0, BOARD_HEIGHT, BOARD_WIDTH, 100};
    SDL_Rect playerOneGoal = {-50, 0, 50, BOARD_HEIGHT};
    SDL_Rect playerTwoGoal = {BOARD_WIDTH, 0, 50, BOARD_HEIGHT};

    // has the ball intersected with top,  bottom, or player rectangles?
    SDL_Rect intersection = {0, 0, 0, 0};
    if (SDL_TRUE == SDL_IntersectRect(&ballRect, &topRect, &intersection) ||
        SDL_TRUE == SDL_IntersectRect(&ballRect, &botRect, &intersection)) {
        _ballY -= _directionY;
        _ballX -= _directionX;

        _directionY = _directionY * -1;
    }

    if (SDL_TRUE ==
            SDL_IntersectRect(&ballRect, &playerOneRect, &intersection) ||
        SDL_TRUE ==
            SDL_IntersectRect(&ballRect, &playerTwoRect, &intersection)) {
        _ballY -= _directionY;
        _ballX -= _directionX;
        _directionX = _directionX * -1;
    }

    // has the ball intersected with the goal rectangles?
    //
    if (SDL_TRUE == SDL_HasIntersection(&ballRect, &playerOneGoal)) {
        std::cout << "PLAYER TWO SCORES!";

        _ballY = INITIAL_BALL_Y;
        _ballX = INITIAL_BALL_X;
    }

    if (SDL_TRUE == SDL_HasIntersection(&ballRect, &playerTwoGoal)) {
        std::cout << "PLAYER ONE SCORE!";

        _ballY = INITIAL_BALL_Y;
        _ballX = INITIAL_BALL_X;
    }

    // render players
    SDL_RenderCopy(_renderer.get(), _block.get(), nullptr, &playerOneRect);
    SDL_RenderCopy(_renderer.get(), _block.get(), nullptr, &playerTwoRect);

    // render ball
    SDL_RenderCopy(_renderer.get(), _ball.get(), nullptr, &ballRect);

    SDL_RenderPresent(_renderer.get());
}

