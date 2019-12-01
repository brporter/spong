#include "resources.h"

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif

std::string ResourceManager::getResource(Resources r)
{
#ifdef __APPLE__
    CFBundleRef bundle;
    bundle = CFBundleGetMainBundle();

    CFURLRef resourcesUrl = CFBundleCopyResourcesDirectoryURL(bundle);

    char path[PATH_MAX];
    if (!CFURLGetFileSystemRepresentation(resourcesUrl, TRUE, (uint8_t*)path,
                                          PATH_MAX)) {
        // todo: do something more sensible
        throw "boom";
    }

    CFRelease(resourcesUrl);

    switch (r) {
        case Resources::Block:
            return std::string(path) + "/spot.bmp";
        case Resources::Ball:
            return std::string(path) + "/ball.bmp";
    }

    return std::string(path);
#endif

#ifdef WIN32
    switch (r)
    {
        case Resources::Block:
            return "spot.bmp";
        case Resources::Ball:
            return "ball.bmp";
    }
#endif

    // TODO: handle windows

    return "";
}
