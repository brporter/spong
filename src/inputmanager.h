#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "input.h"

class IGameObject;

class IInputManager {
public:
    virtual void scan() = 0;s
    virtual void subscribe(Key key, IGameObject& object) = 0;
    virtual void unsubscribe(Key key, IGameObject& object) = 0;
};

class InputManager
    : public IInputManager
{
public:
    void subscribe(Key key, IGameObject& object) override;
    void unsubscribe(Key key, IGameObject& object) override;
};

#endif // INPUTMANAGER_H