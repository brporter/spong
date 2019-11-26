#include "player.h"

#include <iostream>
#include <string>

#include "resources.h"

Player::Player(SDL_Renderer* renderer)
    : _renderer(renderer), _score(0), _position({0})
{
    std::string spotPath = Resources::GetSpot() + "/spot.bmp";

    SDL_Surface* surface = SDL_LoadBMP(spotPath.c_str());

    if (surface == nullptr)
        std::cerr << "Error: " << SDL_GetError() << std::endl;

    _texture.reset(SDL_CreateTextureFromSurface(_renderer, surface));
    SDL_QueryTexture(_texture.get(), nullptr, nullptr, &_textureDimensions.w,
                     &_textureDimensions.h);

    _position.x = 50;
    _position.y = 100;
    _position.h = 50;
    _position.w = 20;

    SDL_FreeSurface(surface);
}

void Player::render()
{
    SDL_RenderCopy(_renderer, _texture.get(), nullptr, &_position);
}

void Player::setScore(uint32_t score) { _score = score; }

void Player::updatePosition(uint32_t pos) { _position.y += pos; }

/*
class Player {
private:
    uint32_t _score;
    SDL_Rect _position;

public:
    Player();
    Player(Player&) = delete;
    Player(Player&&) = delete;

    void render(SDL_Renderer* renderer);
    void setScore(uint32_t score);
    void updatePosition(uint32_t pos);
}
*/
