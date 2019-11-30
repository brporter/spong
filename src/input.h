#ifndef INPUT_H
#define INPUT_H

#include <cstdint>
#include <unordered_map>

enum class Key { Up, Down, W, S, Quit };

class IInputManager {
public:
    virtual const std::unordered_map<Key, uint8_t>& getKeyStates() = 0;
};

class InputManager : IInputManager {
private:
    InputManager(InputManager&) = delete;
    InputManager(InputManager&&) = delete;

    std::unordered_map<Key, uint8_t> _keyState;

public:
    InputManager();
    const std::unordered_map<Key, uint8_t>& getKeyStates() override;
};

#endif  // INPUT_H
