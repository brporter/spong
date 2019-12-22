#ifndef SCORE_H
#define SCORE_H

#include "safesdl.h"

class ScoreBoard {
private:
    Texture _scoreBoard;
    uint32_t _playerOne;
    uint32_t _playerTwo;
    Font _font;

public:
    Texture& get();
    void setScore(uint32_t playerOne, uint32_t playerTwo);
};
#endif  // SCORE_H
