//
//  texture.h
//  HelloSDL
//
//  Created by Bryan Porter on 11/22/19.
//  Copyright © 2019 Bryan Porter. All rights reserved.
//

#ifndef texture_h
#define texture_h

#include <SDL.h>

#include <memory>

namespace internal {
struct TextureDeleter {
    void operator()(SDL_Texture* resource)
    {
        if (nullptr != resource) SDL_DestroyTexture(resource);
    }
};
}  // namespace internal

using Texture = std::unique_ptr<SDL_Texture, internal::TextureDeleter>;

#endif /* texture_h */
