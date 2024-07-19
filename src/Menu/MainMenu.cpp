//
// Created by Matt on 2/07/2024.
//

#include "MainMenu.h"

#include <Managers/InputManager.h>

#include "AboutMenu.h"
#include "DifficultlyMenu.h"
#include "Managers/FontManger.h"
#include "Managers/TextureManger.h"

void MainMenu::Render() {

    int x_pos = 145;
    TextureManger::Instance()->DrawImage(image_id_);
    FontManger::Instance()->RenderText("RaySnake!", 62, {255, 255, 255}, x_pos, 100);
    FontManger::Instance()->RenderText("A new version by MFT", 48, {255, 255, 255}, x_pos, 200);

    SDL_Color col;
    for (auto i = 0; i < options_.size(); i++) {
        if (i == current_selection_) {
            col = {255, 0, 0};
        } else
            col = {255, 255, 255};

        FontManger::Instance()->RenderText(options_[i], 48, col, x_pos, 550 + (i * 50));
    }
}

void MainMenu::Update() {
    if (InputManager::Instance()->IsKeyPress(SDLK_DOWN) || InputManager::Instance()->IsKeyPress(SDLK_s)) {
        current_selection_++;
    } else if (InputManager::Instance()->IsKeyPress(SDLK_UP) || InputManager::Instance()->IsKeyPress(SDLK_w)) {
        current_selection_--;
    } else if (InputManager::Instance()->IsKeyPress(SDLK_RETURN)) {
        if (current_selection_ == 0) {
            game_.SetMenu<DifficultlyMenu>();
        } else if (current_selection_ == 1) {
            game_.SetMenu<AboutMenu>();
        } else if (current_selection_ == 2) {
            game_.Quit();
        }
    }
    current_selection_ = PositiveModulo(current_selection_, num_options_);
}

MainMenu::MainMenu(Game &game) : game_(game) {
    TextureManger::Instance()->LoadText("src/resources/art/background2.png", image_id_);
}

int MainMenu::PositiveModulo(int i, int n) {
    return (i % n + n) % n;
}