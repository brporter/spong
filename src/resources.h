#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>

enum class Resources { Block, Ball };

class ResourceManager {
private:
    ResourceManager() = delete;
    ResourceManager(Resources&) = delete;
    ResourceManager(Resources&&) = delete;
    ~ResourceManager() = default;

public:
    static std::string getResource(Resources r);
};

#endif  // RESOURCES_H
