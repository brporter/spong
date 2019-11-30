#include "input.h"

#include <SDL.h>

InputManager::InputManager() : _keyState() {}

const std::unordered_map<Key, uint8_t>& InputManager::getKeyStates()
{
    const uint8_t* keyStates = SDL_GetKeyboardState(nullptr);

    _keyState[Key::Up] = keyStates[SDL_SCANCODE_UP];
    _keyState[Key::Down] = keyStates[SDL_SCANCODE_DOWN];
    _keyState[Key::W] = keyStates[SDL_SCANCODE_W];
    _keyState[Key::S] = keyStates[SDL_SCANCODE_S];

    SDL_Event e;
    if (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            _keyState[Key::Quit] = 1;
        else
            _keyState[Key::Quit] = 0;
    }

    return _keyState;
}
