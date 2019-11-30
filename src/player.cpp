#include "player.h"

#include <iostream>
#include <string>

Player::Player() : _score(0), _position(0) {}

uint32_t Player::score() const { return _score; }
void Player::setScore(uint32_t score) { _score = score; }

uint32_t Player::position() const { return _position; }
void Player::updatePosition(uint32_t pos) { _position = pos; }

