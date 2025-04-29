/**
 * @class InputManager
 * @brief Singleton class for managing input events in the application.
 *
 * The InputManager class is responsible for handling keyboard input and
 * detecting application quit events. It uses SDL for input event processing
 * and maintains internal mappings to track the state of keys. This class
 * follows the singleton design pattern to ensure a single instance is used
 * throughout the application.
 *
 * Key Features:
 * - Tracks the state of keys (pressed or not).
 * - Detects if the application quit event has been triggered.
 * - Provides an interface to query key states and quit events.
 *
 * Usage:
 * - Call `InputManager::Instance()` to get the singleton instance.
 * - Use `Update()` to process input events every frame.
 * - Query key states using `IsKeyPress(SDL_Keycode key)`.
 * - Check if the quit button was pressed using `QuitButtonPressed()`.
 *
 * @note This class is not copyable or assignable to enforce the singleton
 * pattern.
 */
#pragma once

#include <SDL.h>

#include <memory>
#include <unordered_map>

class InputManager {
public:
  static InputManager *Instance() {
    if (!s_instance_)
      s_instance_ = std::unique_ptr<InputManager>(new InputManager);
    return s_instance_.get();
  }
  ~InputManager() = default;
  InputManager(const InputManager *) = delete;
  InputManager *operator=(const InputManager *) = delete;

  void Update();
  bool IsKeyPress(SDL_Keycode key);
  [[nodiscard]] bool QuitButtonPressed() const { return quit_application_; }

private:
  InputManager() = default;
  static std::unique_ptr<InputManager> s_instance_;
  std::unordered_map<SDL_Keycode, bool> key_map_;
  std::unordered_map<SDL_Keycode, bool> key_read_;
  bool quit_application_ = false;
};
