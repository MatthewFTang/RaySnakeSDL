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
    InputManager(const InputManager *) = delete;
    InputManager *operator=(const InputManager *) = delete;

    void Update();
    bool IsKeyPress(SDL_Keycode key);
    [[nodiscard]] bool QuitButtonPressed() const {return quit_application_;}


private:
    InputManager() = default;
    static InputManager *s_instance_;
    std::unordered_map<SDL_Keycode, bool> key_map_;
    std::unordered_map<SDL_Keycode, bool> key_read_;
    bool quit_application_ =false;
};
