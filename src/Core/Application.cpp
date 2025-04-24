//
// Application.cpp
// Created by Matt on 2/07/2024.
//
// This file implements the `Application` class, which serves as the core of the
// application. It handles initialization, the main loop, rendering, updating,
// and cleanup of the application.
//

#include "Application.h"

#include <SDL_ttf.h>
#include <iostream>

#include "Game.h"
#include "Managers/InputManager.h"
#include <memory.h>
#include <stdexcept>
#include <string>
// Static instance of the Application singleton.
Application *Application::s_instance_ = nullptr;

// Starts the main application loop.
void Application::Run() {
  Initialise(); // Initialize SDL, window, renderer, and other resources.
  Loop();       // Enter the main application loop.
  Clean();      // Clean up resources after exiting the loop.
}

// Initializes the application, including SDL, the window, and the renderer.
void Application::Initialise() {
  // Initialize SDL video subsystem.
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    throw std::runtime_error(
        std::string("SDL could not initialize! SDL_Error: ") + SDL_GetError());
  }
  // Create the SDL window.
  window_ = SDL_CreateWindow("SDL Test", 100, 100, params_.window_width,
                             params_.window_height, 0);
  if (!window_) {
    throw std::runtime_error(
        std::string("Window could not be created! SDL_Error: ") +
        SDL_GetError());
    return;
  }

  // Create the SDL renderer.
  renderer_ = SDL_CreateRenderer(window_, -1, 0);
  if (!renderer_) {
    throw std::runtime_error(
        std::string("Renderer could not be created! SDL_Error: ") +
        SDL_GetError());
    SDL_DestroyWindow(window_);
    SDL_Quit();
    return;
  }

  // Initialize SDL audio subsystem.
  if (SDL_Init(SDL_INIT_AUDIO) < 0) {
    throw std::runtime_error(
        std::string("SDL could not initialize audio! SDL_Error: ") +
        SDL_GetError());
  }

  // Initialize SDL_ttf for font rendering.
  if (TTF_Init() < 0) {
    throw std::runtime_error(std::string("Error initializing SDL_ttf: ") +
                             TTF_GetError());
  }

  // Create the game instance.
  game_ = std::make_unique<Game>();

  // Retrieve the window size.
  SDL_GetWindowSize(window_, &screen_width_, &screen_height_);
}

// Main application loop that runs until the game signals to stop.
void Application::Loop() {
  while (game_->GetRunning()) {
    Render(); // Render the current frame.
    Update(); // Update the game state and handle input.
  }
}

// Cleans up resources used by the application.
void Application::Clean() {
  Game::Clean();                  // Clean up game-specific resources.
  SDL_DestroyRenderer(renderer_); // Destroy the SDL renderer.
  SDL_DestroyWindow(window_);     // Destroy the SDL window.
  SDL_Quit();                     // Quit SDL subsystems.
}

// Renders the current frame.
void Application::Render() {
  // Set the renderer's draw color to the background color.
  SDL_SetRenderDrawColor(renderer_, background_color_.r, background_color_.g,
                         background_color_.b, 255);

  // Clear the screen with the background color.
  SDL_RenderClear(renderer_);

  // Render the game-specific content.
  game_->Render();

  // Wait to maintain a consistent frame rate (e.g., 15ms per frame).
  while (SDL_GetTicks() - last_frame_time_ < 15) {
    // Busy-wait until the frame time has elapsed.
  }

  // Present the rendered frame to the screen.
  SDL_RenderPresent(renderer_);

  // Update the last frame time.
  last_frame_time_ = SDL_GetTicks();
}

// Updates the application state, including the game and input handling.
void Application::Update() const {
  game_->Update();                    // Update the game state.
  InputManager::Instance()->Update(); // Update input handling.
}
