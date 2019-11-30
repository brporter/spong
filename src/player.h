#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>

#include <cstdint>

class Player {
private:
    uint32_t _score;
    uint32_t _position;

public:
    Player();
    Player(Player&) = delete;
    Player(Player&&) = delete;

    uint32_t score() const;
    void setScore(uint32_t score);
    uint32_t position() const;
    void updatePosition(uint32_t pos);
};

#endif  // PLAYER_H
