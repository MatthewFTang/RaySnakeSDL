//
// Created by Matt on 2/07/2024.
//

#include "Application.h"

#include <SDL2_ttf/SDL_ttf.h>

#include <iostream>

#include "Game.h"
#include "Managers/InputManager.h"
Application *Application::s_instance_ = nullptr;

void Application::Run() {
  Initialise();
  Loop();
  Clean();
}
void Application::Initialise() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError()
              << std::endl;
  }
  window_ = SDL_CreateWindow("SDL Test", 100, 100, params_.window_width,
                             params_.window_height, 0);
  if (!window_) {
    std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    return;
  }
  renderer_ = SDL_CreateRenderer(window_, -1, 0);

  if (!renderer_) {
    std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    SDL_DestroyWindow(window_);
    SDL_Quit();
    return;
  }
  if (SDL_Init(SDL_INIT_AUDIO) < 0) {
    std::cerr << "SDL could not initialize audio SDL_Error: " << SDL_GetError()
              << std::endl;
  }
  if (TTF_Init() < 0) {
    std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
  }
  game_ = new Game();

  SDL_GetWindowSize(window_, &screen_width_, &screen_height_);
}

void Application::Loop() {

  while (game_->GetRunning()) {
    Render();
    Update();
  }
}

void Application::Clean() {
  game_->Clean();
  delete game_;
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}
void Application::Render() {
  SDL_SetRenderDrawColor(renderer_, background_color_.r, background_color_.g,
                         background_color_.b, 255);
  SDL_RenderClear(renderer_);

  game_->Render();
  while (SDL_GetTicks() - last_frame_time_ < 15) {
    //Waits until time
  }
  SDL_RenderPresent(renderer_);
  last_frame_time_ = SDL_GetTicks();
}

void Application::Update() const {
  game_->Update();
  InputManager::Instance()->Update();
}
