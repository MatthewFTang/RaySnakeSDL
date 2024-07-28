//
// Created by Matt on 2/07/2024.
//
#include "Game.h"

#include "GameDifficulty.h"
#include "Level.h"
#include "Managers/FontManger.h"
#include "Managers/InputManager.h"
#include "Managers/SoundManger.h"
#include "Managers/TextureManger.h"
#include "Menu/MainMenu.h"

Game::Game() {

  SetMenu<MainMenu>();
  SoundManger::Instance()->Load("src/resources/audio/Instrumental.mp3",
								"background_music", "music");
  SoundManger::Instance()->Load("src/resources/audio/Theme1.mp3",
								"theme_music", "music");
  SoundManger::Instance()->Play("theme_music", true);
}

void Game::Clean() {
  TextureManger::Instance()->CleanAll();
  SoundManger::Instance()->Clean();
}
void Game::Render() const {
  if (menu_) {
	menu_->Render();
  } else {
	level_->Render();
  }
  SoundManger::Instance()->Render();
}
void Game::Update() {
  if (menu_) {
	menu_->Update();
  } else {
	level_->Update();
  }

  if (InputManager::Instance()->IsKeyPress(SDLK_ESCAPE)) {
	SetMenu<MainMenu>();
	SoundManger::Instance()->Pause("background_music");
	SoundManger::Instance()->Play("theme_music", true);
  }
  if (InputManager::Instance()->QuitButtonPressed()) {
	Quit();
  }
}
void Game::Quit() {
  Clean();
  running_ = false;
}
void Game::Play() {
  menu_ = nullptr;

  running_ = true;
  SoundManger::Instance()->Pause("theme_music");
  SoundManger::Instance()->Play("background_music", true);
}
void Game::NewGame(GameDifficulty difficulty) {
  level_ = std::make_unique<Level>(difficulty);
}
