#ifndef SCORE_H
#define SCORE_H

#include "safesdl.h"

class ScoreBoard {
private:
    Surface _scoreBoard;
    uint32_t _playerOne;
    uint32_t _playerTwo;
    Font _font;

public:
    SDL_Surface* get();
    void setScore(uint32_t playerOne, uint32_t playerTwo);
};
#endif  // SCORE_H
