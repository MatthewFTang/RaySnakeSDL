//
// Application.h
// Created by Matthew Tang on 2/07/2024.
//
// This header file defines the `Application` class, which serves as the core of
// the application. It manages the initialization, main loop, rendering, and
// cleanup of the application, as well as providing access to the SDL window and
// renderer.
//
// The `Application` class is implemented as a singleton to ensure only one
// instance exists.
//

#pragma once

#include "Core/Game.h"
#include <SDL.h>

// Struct to hold application configuration parameters.
struct ApplicationParameters {
  const char *title = "RaySnake"; // Title of the application window.
  bool full_screen = false; // Whether the application runs in fullscreen mode.
  const int window_width = 1000; // Width of the application window.
  const int window_height = 800; // Height of the application window.
};

// The main application class.
// This class is responsible for managing the SDL window, renderer, and
// application loop.
// It is implemented as a singleton to ensure that only one instance exists
// throughout the application lifecycle.
// The class provides methods for initialization, rendering, updating, and
// cleanup.
class Application {

public:
  // Returns the singleton instance of the Application class.
  static Application *Instance() {
    if (!s_instance_) {
      s_instance_ = new Application();
    }
    return s_instance_;
  }

  // Destructor: Cleans up resources and deletes the singleton instance.
  ~Application() {
    Clean();
    delete s_instance_;
  }

  // Returns the SDL renderer used by the application.
  [[nodiscard]] SDL_Renderer *GetRenderer() const { return renderer_; }

  // Returns the SDL window used by the application.
  [[nodiscard]] SDL_Window *GetWindow() const { return window_; }

  // Returns the width of the application screen.
  [[nodiscard]] int GetScreenWidth() const { return screen_width_; }

  // Returns the height of the application screen.
  [[nodiscard]] int GetScreenHeight() const { return screen_height_; }

  // Starts the main application loop.
  void Run();

  // Static pointer to the singleton instance.
  static Application *s_instance_;

private:
  // Private constructor to enforce the singleton pattern.
  Application() = default;

  // Initializes the application (e.g., SDL, window, renderer, etc.).
  void Initialise();

  // Renders the current frame.
  void Render();

  // Updates the application state.
  void Update() const;

  // Main application loop.
  void Loop();

  // Cleans up resources used by the application.
  void Clean();

  // Background color of the application window.
  const SDL_Color background_color_ = {
      249, // Red
      123, // Green
      54,  // Blue
      255  // Alpha (opacity)
  };

  // Application configuration parameters.
  const ApplicationParameters params_ = ApplicationParameters();

  // Pointer to the SDL window.
  SDL_Window *window_ = nullptr;

  // Pointer to the SDL renderer.
  SDL_Renderer *renderer_ = nullptr;

  // Time of the last frame, used for frame timing.
  double last_frame_time_ = 0.0;

  // Pointer:h  to the game instance managed by the application.
  Game *game_ = nullptr;

  // Screen height in pixels.
  int screen_height_ = 0;

  // Screen width in pixels.
  int screen_width_ = 0;
};
