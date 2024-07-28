//
// Created by Matt on 2/07/2024.
//

#pragma once

#include <memory>

#include "Level.h"
#include "Menu/Menu.h"

class Level;
class Game {
public:
  Game();
  ~Game() = default;

  static void Clean();
  void Render() const;
  void Update();
  void Play();
  void Quit();
  [[nodiscard]] bool GetRunning() const { return running_; }

  template <typename T> void SetMenu() { menu_ = std::make_shared<T>(*this); }
  void NewGame(GameDifficulty difficulty);

private:
  bool running_ = true;
  std::unique_ptr<Level> level_;

  std::shared_ptr<Menu> menu_;
};
