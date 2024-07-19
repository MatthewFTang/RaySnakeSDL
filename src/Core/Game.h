//
// Created by Matt on 2/07/2024.
//

#pragma once

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

#include "Level.h"
#include "Menu/Menu.h"
#include "Objects/GameObject.h"

class Level;
class Game {
public:
    Game();
    ~Game() = default;

    void Clean() const;
    void Render();
    void Update();
    void Play();
    void Quit();
    bool GetRunning() const { return running_; }

    template<typename T>
    void SetMenu() {
        menu_ = std::make_shared<T>(*this);
    }
    void NewGame(GameDifficulty difficulty);

private:
    bool running_ = true;
    std::unique_ptr<Level> level_;

    std::shared_ptr<Menu> menu_;
};
