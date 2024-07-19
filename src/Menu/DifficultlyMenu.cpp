

#include "DifficultlyMenu.h"

#include "Core/Application.h"
#include "Managers/FontManger.h"
#include "Managers/InputManager.h"
#include "Managers/TextureManger.h"

void DifficultlyMenu::Render() {
    TextureManger::Instance()->DrawImage("mainMenu");

    SDL_Color col;
    int win_height = Application::Instance()->GetScreenHeight();
    int win_width = Application::Instance()->GetScreenWidth();
    int x_pos = win_width / 2;
    int y_pos = win_height / 2 - 100;
    for (auto i = 0; i < options_.size(); i++) {
        if (i == current_selection_) {
            col = {255, 0, 0};
        } else
            col = {255, 255, 255};

        FontManger::Instance()->RenderText(options_[i], 48, col, x_pos, y_pos + (i * 50), true);
    }
}

void DifficultlyMenu::Update() {


    if (InputManager::Instance()->IsKeyPress(SDLK_DOWN)) {
        current_selection_++;
    } else if (InputManager::Instance()->IsKeyPress(SDLK_UP)) {
        current_selection_--;
    } else if (InputManager::Instance()->IsKeyPress(SDLK_RETURN)) {
        using enum GameDifficulty;
        GameDifficulty difficulty;
        if (current_selection_ == 0) {
            difficulty = EASY;
        } else if (current_selection_ == 1) {
            difficulty = MEDIUM;
        } else {
            difficulty = HARD;
        }
        game_.NewGame(difficulty);
        game_.Play();
    }


    current_selection_ = PositiveModulo(current_selection_, num_options_);
}
int DifficultlyMenu::PositiveModulo(int i, int n) {
    return (i % n + n) % n;
}
DifficultlyMenu::DifficultlyMenu(Game &game) : game_(game) {
}
