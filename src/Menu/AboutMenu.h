//
// Created by Matt on 3/07/2024.
//

#pragma once

#include <string>

#include "Menu.h"
class Game;
class AboutMenu : public Menu {
public:
    explicit AboutMenu(Game &game);
    void Render() override;
    void Update() override;

private:
    Game &game_;
    std::string texture_id_= "aboutMenu";

};
