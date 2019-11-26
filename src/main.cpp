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

#include "player.h"
#include "input.h"
#include "resources.h"
#include "texture.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 1024;
const int FPS = 60;
const int FrameTime = 1000 / FPS;

int main(int argc, const char *argv[])
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Hello, World", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (nullptr == renderer)
        std::cerr << "Error: " << SDL_GetError() << std::endl;

    std::string resourcePath = Resources::GetSpot();
    resourcePath += "/spot.bmp";

    Player p(renderer);
    InputManager im;

    bool running = true;
    while (running) {
        int frameStart = SDL_GetTicks();

        SDL_Event e;

        auto keyState = im.getKeyStates();

        if (keyState[Key::Quit])
        {
            break;
        }

        if (keyState[Key::Up])
        {
            p.updatePosition(-10);
        }

        if (keyState[Key::Down])
        {
            p.updatePosition(10);
        }

        SDL_RenderClear(renderer);
        p.render();

        // SDL_RenderCopy(renderer, bitmapTex.get(), nullptr, &spot);
        SDL_RenderPresent(renderer);

        int frameStop = SDL_GetTicks();
        int frameTook = frameStop - frameStart;

        if (FrameTime > frameTook) SDL_Delay(FrameTime - frameTook);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
