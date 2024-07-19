
#include "InputManager.h"


InputManager* InputManager::s_instance_ = nullptr;
void InputManager::Update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.repeat == 0) {
                    key_map_[event.key.keysym.sym] = true;
                    key_read_[event.key.keysym.sym] = false;
                }
                break;
            case SDL_KEYUP:
                if (event.key.repeat == 0) { key_map_[event.key.keysym.sym] = false; }
                break;
            default:
                break;
        }
    }
}
bool InputManager::IsKeyPress(SDL_Keycode key) {
    auto it = key_map_.find(key);
    if (it != key_map_.end() && !key_read_[key]) {
        key_read_[key] = true;
        return it->second;
    }
    return false;
}
