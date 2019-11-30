//
//  main.cpp
//  HelloSDL
//
//  Created by Bryan Porter on 11/19/19.
//  Copyright © 2019 Bryan Porter. All rights reserved.
//

#include <SDL.h>

#include <cstdio>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "board.h"
#include "input.h"

const int FPS = 60;
const int FrameTime = 1000 / FPS;

int main(int argc, const char *argv[])
{
    Board b;
    InputManager im;

    bool running = true;
    while (running) {
        int frameStart = SDL_GetTicks();

        SDL_Event e;

        auto keyState = im.getKeyStates();

        if (keyState[Key::Quit]) {
            break;
        }

        if (keyState[Key::Up]) {
            b.playerTwo().updatePosition(b.playerTwo().position() - 30);
        }

        if (keyState[Key::Down]) {
            b.playerTwo().updatePosition(b.playerTwo().position() + 30);
        }

        if (keyState[Key::W]) {
            b.playerOne().updatePosition(b.playerOne().position() - 30);
        }

        if (keyState[Key::S]) {
            b.playerOne().updatePosition(b.playerOne().position() + 30);
        }

        b.render();

        int frameStop = SDL_GetTicks();
        int frameTook = frameStop - frameStart;

        if (FrameTime > frameTook) SDL_Delay(FrameTime - frameTook);
    }

    return 0;
}
