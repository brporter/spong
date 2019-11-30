//
//  texture.h
//  HelloSDL
//
//  Created by Bryan Porter on 11/22/19.
//  Copyright © 2019 Bryan Porter. All rights reserved.
//

#ifndef SAFESDL_H
#define SAFESDL_H

#include <SDL.h>

#include <memory>

namespace internal {
struct TextureDeleter {
    void operator()(SDL_Texture* resource)
    {
        if (nullptr != resource) SDL_DestroyTexture(resource);
    }
};

struct WindowDeleter {
    void operator()(SDL_Window* window)
    {
        if (nullptr != window) SDL_DestroyWindow(window);
    }
};

struct RendererDeleter {
    void operator()(SDL_Renderer* renderer)
    {
        if (nullptr != renderer) SDL_DestroyRenderer(renderer);
    }
};
}  // namespace internal
using Texture = std::unique_ptr<SDL_Texture, internal::TextureDeleter>;
using Renderer = std::unique_ptr<SDL_Renderer, internal::RendererDeleter>;
using Window = std::unique_ptr<SDL_Window, internal::WindowDeleter>;

#endif  // SAFESDL_H
