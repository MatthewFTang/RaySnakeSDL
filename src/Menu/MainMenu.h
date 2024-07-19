//
// Created by Matt on 2/07/2024.
//

#pragma once
#include <vector>

#include "Core/Game.h"
#include "Menu.h"

class Game;
class MainMenu : public Menu {
public:
    void Render() override;
    void Update() override;
    explicit MainMenu(Game &game);

private:
    std::vector<const char *> options_ = {"Play", "About", "Exit"};
    int num_options_ = (int) options_.size();

    Game &game_;
    int current_selection_ = 0;
    double last_press_time_ = 0.0;
    std::string image_id_ = "mainMenu";
    static int PositiveModulo(int i, int n);
};
