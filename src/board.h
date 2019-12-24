#ifndef BOARD_H
#define BOARD_H

#include <SDL.h>
#include <SDL_ttf.h>

#include <vector>

#include "player.h"
#include "safesdl.h"

const int32_t BOARD_HEIGHT = 1024;
const int32_t BOARD_WIDTH = 1280;

class IBoard {
public:
    virtual Player& playerOne() = 0;
    virtual Player& playerTwo() = 0;
    virtual void render() = 0;
};

class Board : IBoard {
private:
    Window _window;
    Renderer _renderer;
    Texture _ball;
    Texture _block;
    Texture _scoreBoard;
    Player _playerOne;
    Player _playerTwo;
    TTF_Font* font;

    bool _inCollision;

    const int32_t INITIAL_BALL_X = (BOARD_WIDTH / 2) - 25;
    const int32_t INITIAL_BALL_Y = (BOARD_HEIGHT / 2) - 25;

    // TOOD: move to ball object
    int32_t _ballX;
    int32_t _ballY;
    int32_t _directionX;  // TODO: move to vector class
    int32_t _directionY;

public:
    Board();
    ~Board();

    /* No copy, move, or assignments */
    Board(const Board&) = delete;
    Board(Board&&) = delete;

    Board& operator=(const Board&) = delete;
    Board& operator=(Board&&) = delete;

    Player& playerOne() override;
    Player& playerTwo() override;
    void render() override;
};

#endif  // BOARD_H
