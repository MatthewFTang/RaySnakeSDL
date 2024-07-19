//
// Created by Matt on 15/07/2024.
//

#include "Level.h"

#include <format>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "BaseParams.h"
#include "Core/Application.h"
#include "Managers/FontManger.h"
#include "Managers/InputManager.h"
#include "Managers/SoundManger.h"
#include "Managers/TextureManger.h"
#include "Objects/Food.h"
#include "Objects/GameObject.h"
#include "Objects/Player.h"

Level::Level(GameDifficulty difficulty) : difficulty_(difficulty) {
    SoundManger::Instance()->Load("src/resources/audio/short_bite.mp3", "bite");
    SoundManger::Instance()->Load("src/resources/audio/esm_8_bit_game_over_1_arcade_80s_simple_alert_notification_game.mp3", "game_over");
    TextureManger::Instance()
            ->LoadText("src/resources/assets/Brown.png", "background_tile");


    auto x_max_width = Application::Instance()->GetScreenWidth() - x_max_;
    n_cols_tiles_ = (int) std::floor(x_max_width / background_size_);
    x_actual_max_ = x_min_ + (float) n_cols_tiles_ * background_size_;

    auto y_max_height = Application::Instance()->GetScreenHeight() - y_max_;
    n_rows_tiles_ = (int) std::floor(y_max_height / background_size_);
    y_actual_max_ = y_min_ + (float) n_rows_tiles_ * background_size_;
    Reset();
}
void Level::Reset() {
    AddPlayer();
    AddFruit();
    SoundManger::Instance()->Play("background_music", true);

    playing_ = true;
    score_ = 0;
    start_time_ = SDL_GetTicks();
}

void Level::Render() {
    DrawBackground();
    ShowScore();
    if (playing_) {
        player_->Render();
        fruit_->Render();
    }

    if (!playing_) {
        auto x_pos = (int) (x_min_ + (x_actual_max_ - x_min_) / 2);
        auto y_pos = (int) (y_min_ + (y_actual_max_ - y_min_) / 2);

        FontManger::Instance()->RenderText("Game over!", 48, {255, 0, 0},
                                           x_pos,
                                           y_pos - 150,
                                           true);
        FontManger::Instance()->RenderText("Press R to restart ", 32, {255, 0, 0},
                                           x_pos,
                                           y_pos - 100, true);
        FontManger::Instance()->RenderText("Press ESCAPE to go to main menu", 32, {255, 0, 0},
                                           x_pos,
                                           y_pos + 50, true);
        if (InputManager::Instance()->IsKeyPress(SDLK_r)) {
            Reset();
        }
    }
}
void Level::Update() {
    if (playing_) {
        player_->Update();
        fruit_->Update();
        CheckCollision();

        current_time_ = SDL_GetTicks() - start_time_;
    }
    if (score_ > high_score_) {
        high_score_ = score_;
    }
}


void Level::CheckCollision() {

    SDL_Rect player_bounding_box = player_->GetBoundingBox();

    if (player_->HitTail() || player_bounding_box.x < x_min_ || player_bounding_box.x > x_actual_max_ || player_bounding_box.y < y_min_ || player_bounding_box.y > y_actual_max_) {
        playing_ = false;
        SoundManger::Instance()->Play("game_over", true);
        SoundManger::Instance()->Pause("background_music");
    }
    SDL_Rect fruit_box = fruit_->GetBoundingBox();
    player_bounding_box.x += 5;
    player_bounding_box.y += 5;
    player_bounding_box.w -= 10;
    player_bounding_box.h -= 10;

    if (CheckCollisionRecs(player_bounding_box, fruit_box)) {
        SoundManger::Instance()->Play("bite", true);
        AddFruit();
        player_->IncrementTail();
        score_++;
    }
}

void Level::AddPlayer() {
    PlayerInfo p;
    auto player_params = LoaderParams(p.file_path, p.x, p.y, p.sprite_width, p.sprite_height, "player", p.num_frames, p.animation_speed, p.dest_width, p.dest_height, p.items_per_row);
    player_ = std::make_unique<Player>(player_params);
    if (difficulty_ == GameDifficulty::EASY) {
        player_->SetMovementSpeed(2.0f);
    } else if (difficulty_ == GameDifficulty::MEDIUM) {
        player_->SetMovementSpeed(4.0f);
    } else
        player_->SetMovementSpeed(8.0f);
    player_->NewGame();
}

void Level::AddFruit() {
    FoodInfo p;

    auto new_loc = player_->NewFruitLocation((int) (x_actual_max_ - x_min_) - 20, (int) (y_actual_max_ - y_min_) - 20);
    p.x = 10 + (int) (x_min_ + new_loc.x);
    p.y = 10 + (int) (y_min_ + new_loc.y);

    auto food_params = LoaderParams(p.file_path, p.x, p.y, p.sprite_width, p.sprite_height, "food", p.num_frames, p.animation_speed, p.dest_width, p.dest_height, p.items_per_row);
    fruit_ = std::make_unique<Food>(food_params);
}


void Level::ShowScore() const {

    std::string num_s = std::to_string(score_);
    std::string text = "Score \n" + num_s;
    int *win_w;
    SDL_GetWindowSize(Application::Instance()->GetWindow(), win_w, nullptr);
    int x_pos = *win_w - 150;
    FontManger::Instance()->RenderText(text.c_str(), 48, {255, 255, 255}, x_pos, 50);

    num_s = std::to_string(high_score_);
    text = "High \nscore \n" + num_s;
    FontManger::Instance()->RenderText(text.c_str(), 48, {255, 255, 255}, x_pos, 250);

    std::stringstream stream;
    num_s = std::format("{:.2f}", current_time_);

    text = "Time \n" + num_s;
    FontManger::Instance()->RenderText(text.c_str(), 48, {255, 255, 255}, x_pos, 650);
}

void Level::DrawBackground() const {

    for (int x = 0; x < n_cols_tiles_; x++) {
        for (int y = 0; y < n_rows_tiles_; y++) {
            auto x1 = x_min_ + x * background_size_;
            auto y1 = y_min_ + y * background_size_;
            TextureManger::Instance()->DrawImageWithSize("background_tile", x1, y1, background_size_, background_size_);
        }
    }
    //    DrawLineEx({x_min_, y_min_}, {x_actual_max_, y_min_}, 4, {0, 0, 0});
    //    DrawLineEx({x_min_, y_actual_max_}, {x_actual_max_, y_actual_max_}, 4, BLACK);
    //    DrawLineEx({x_min_, y_min_}, {x_min_, y_actual_max_}, 4, BLACK);
    //    DrawLineEx({x_actual_max_, y_min_}, {x_actual_max_, y_actual_max_}, 4, BLACK);
}
bool Level::CheckCollisionRecs(SDL_Rect rect, SDL_Rect rect_1) {
    return false;
}
