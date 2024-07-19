#pragma once

#include <SDL2/SDL.h>

#include <unordered_map>

class InputManager {
public:
    static InputManager *Instance() {
        if (s_instance_ == nullptr)
            s_instance_ = new InputManager();
        return s_instance_;
    }
    ~InputManager() = default;

    void Update();
    bool IsKeyPress(SDL_Keycode key);
    InputManager(const InputManager *) = delete;
    InputManager *operator=(const InputManager *) = delete;

private:
    InputManager() = default;
    static InputManager *s_instance_;
    std::unordered_map<SDL_Keycode, bool> key_map_;
    std::unordered_map<SDL_Keycode, bool> key_read_;
};
