#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>

enum class NotificationType;
class INotification;
struct Rectangle;
struct Position;

/* Abstract base class for all game objects. */
class IGameObject
{
    public:
        virtual std::string& name() = 0;
        virtual int resourceId() = 0;

        virtual Rectangle& rect() = 0;
        virtual void setRect(Rectangle rect) = 0;

        virtual Position& pos() = 0;
        virtual void setPosition(Position pos) = 0;

        virtual void notify(INotification* notification, NotificationType type) = 0;
};

#endif