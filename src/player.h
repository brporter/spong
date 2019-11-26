#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>

#include <cstdint>

#include "texture.h"

class Player {
private:
    uint32_t _score;
    SDL_Rect _position;
    SDL_Rect _textureDimensions;
    Texture _texture;
    SDL_Renderer* _renderer;

public:
    Player() = delete;
    Player(SDL_Renderer* renderer);
    Player(Player&) = delete;
    Player(Player&&) = delete;

    void render();
    void setScore(uint32_t score);
    void updatePosition(uint32_t pos);
};

#endif  // PLAYER_H
