#include "score.h"

#include <sstream>
#include <string>

Texture& ScoreBoard::get() { return _scoreBoard; }

void ScoreBoard::setScore(uint32_t playerOne, uint32_t playerTwo)
{
    if (playerOne != _playerOne || playerTwo != _playerTwo) {
        // score has changed
        _playerOne = playerOne;
        _playerTwo = playerTwo;

        std::string text;
        std::stringstream textStream(text);

        textStream << _playerOne << " - " << _playerTwo;

        SDL_Color textColor = {255, 0, 0};
        SDL_Surface* scoreBoard = TTF_RenderText_Solid(
            _font.get(), textStream.str().c_str(), textColor);
        SDL_Rect scoreBoardSize = {0};
        _scoreBoard.reset(
            SDL_CreateTextureFromSurface(_renderer.get(), scoreBoard));
        SDL_QueryTexture(_scoreBoard.get(), NULL, NULL, &scoreBoardSize.w,
                         &scoreBoardSize.h);

        SDL_FreeSurface(scoreBoard);
    }
}
