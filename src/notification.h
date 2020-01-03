#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <vector>

class IGameObject;
enum class Key;

class INotification
{
    public:
        virtual IGameObject* object() = 0;
        virtual std::vector<Key>* keyStates() = 0;
};

#endif