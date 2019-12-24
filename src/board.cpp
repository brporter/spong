#include "board.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>

#include "resources.h"

Board::Board()
    : _window(nullptr),
      _renderer(nullptr),
      _ball(nullptr),
      _scoreBoard(nullptr),
      _playerOne(),
      _playerTwo(),
      _ballX(INITIAL_BALL_X),
      _ballY(INITIAL_BALL_Y),
      _directionX(0),
      _directionY(0)
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    font = TTF_OpenFont("Aerocentrix.ttf", 100);
    if (font == nullptr) {
        throw "failed to open font";
    }

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

    TTF_Quit();
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
        if (_directionX < 0) {
            _ballX += intersection.w + 1;
        }
        else {
            _ballX -= intersection.w + 1;
        }

        _directionX = _directionX * -1;
    }

    // has the ball intersected with the goal rectangles?
    bool scoreChanged = false;
    if (SDL_TRUE == SDL_HasIntersection(&ballRect, &playerOneGoal)) {
        std::cout << "PLAYER TWO SCORES!";
        _playerTwo.setScore(_playerTwo.score() + 1);
        scoreChanged = true;

        _ballY = INITIAL_BALL_Y;
        _ballX = INITIAL_BALL_X;
    }

    if (SDL_TRUE == SDL_HasIntersection(&ballRect, &playerTwoGoal)) {
        std::cout << "PLAYER ONE SCORE!";
        _playerOne.setScore(_playerOne.score() + 1);
        scoreChanged = true;

        _ballY = INITIAL_BALL_Y;
        _ballX = INITIAL_BALL_X;
    }

    // calculate scoreboard

    if (scoreChanged || nullptr == _scoreBoard.get())
    {
        std::string text;
        std::stringstream textStream(text);

        textStream << _playerOne.score() << " - " << _playerTwo.score();

        SDL_Color textColor = { 255, 0, 0 };
        SDL_Surface* scoreBoard =
            TTF_RenderText_Solid(font, textStream.str().c_str(), textColor);
        SDL_Texture* scoreBoardTex =
            SDL_CreateTextureFromSurface(_renderer.get(), scoreBoard);

        _scoreBoard.reset(scoreBoardTex);
        SDL_FreeSurface(scoreBoard);
    }

    SDL_Rect scoreBoardSize = { 0 };
    SDL_QueryTexture(_scoreBoard.get(), NULL, NULL, &scoreBoardSize.w,
        &scoreBoardSize.h);

    // render players
    SDL_RenderCopy(_renderer.get(), _block.get(), nullptr, &playerOneRect);
    SDL_RenderCopy(_renderer.get(), _block.get(), nullptr, &playerTwoRect);

    // render scoreboard
    SDL_RenderCopy(_renderer.get(), _scoreBoard.get(), nullptr, &scoreBoardSize);

    // render ball
    SDL_RenderCopy(_renderer.get(), _ball.get(), nullptr, &ballRect);

    SDL_RenderPresent(_renderer.get());
}

