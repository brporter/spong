#include "resources.h"

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif

std::string Resources::GetSpot()
{
#ifdef __APPLE__
    CFBundleRef bundle;
    bundle = CFBundleGetMainBundle();

    CFURLRef resourcesUrl = CFBundleCopyResourcesDirectoryURL(bundle);

    char path[PATH_MAX];
    if (!CFURLGetFileSystemRepresentation(resourcesUrl, TRUE, (uint8_t*)path, PATH_MAX))
    {
        throw "boom";
    }

    CFRelease(resourcesUrl);

    return std::string(path);
#endif
}
