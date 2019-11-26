#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>

class Resources
{
private:
    Resources() = delete;
    Resources(Resources&) = delete;
    Resources(Resources&&) = delete;
    ~Resources() = default;

public:
    static std::string GetSpot();
};

#endif // RESOURCES_H
