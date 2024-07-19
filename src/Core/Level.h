//
// Created by Matt on 15/07/2024.
//

#pragma once

#include <vector>

#include "GameDifficulty.h"
#include "Objects/Food.h"
#include "Objects/Player.h"

class GameObject;

class Level {

public:
    explicit Level(GameDifficulty difficulty);
    ~Level() = default;
    void Render();
    void Update();

    void Reset();

private:
    void
    CheckCollision();

    void AddFruit();
    void AddPlayer();
    void DrawBackground() const;
    void ShowScore() const;

    bool playing_;
    int x_min_ = 20;
    int y_min_ = 20;
    int x_max_ = 200;
    int y_max_ = 40;
    int background_size_ = 50;
    int x_actual_max_;
    int y_actual_max_;
    int n_cols_tiles_;
    int n_rows_tiles_;
    int high_score_ = 0;
    double start_time_;
    double current_time_;
    std::unique_ptr<Player> player_;
    std::unique_ptr<Food> fruit_;
    GameDifficulty difficulty_;
    SDL_Rect rect_1_;
    SDL_Rect rect_2_;
    SDL_Rect rect_3_;
    SDL_Rect rect_4_;

    int score_;
     [[nodiscard]] static bool CheckCollisionRecs(SDL_Rect rect, SDL_Rect rect_1) ;
};
