//
// Created by Matt on 15/07/2024.
//

#include "Level.h"

#include <format>
#include <sstream>

#include "BaseParams.h"
#include "Core/Application.h"
#include "Managers/FontManger.h"
#include "Managers/InputManager.h"
#include "Managers/SoundManger.h"
#include "Managers/TextureManger.h"
#include "Objects/Food.h"
#include "Objects/Player.h"

Level::Level(GameDifficulty difficulty) : difficulty_(difficulty) {
  SoundManger::Instance()->Load("src/resources/audio/short_bite.mp3", "bite",
                                "effect");
  SoundManger::Instance()->Load(
      "src/resources/audio/"
      "esm_8_bit_game_over_1_arcade_80s_simple_alert_notification_game.mp3",
      "game_over", "effect");
  TextureManger::Instance()->LoadText("src/resources/assets/Brown.png",
                                      "background_tile");

  auto x_max_width = Application::Instance()->GetScreenWidth() - x_max_;
  n_cols_tiles_ = (int)std::floor(x_max_width / background_size_);
  x_actual_max_ = x_min_ + n_cols_tiles_ * background_size_;

  auto y_max_height = Application::Instance()->GetScreenHeight() - y_max_;
  n_rows_tiles_ = (int)std::floor(y_max_height / background_size_);
  y_actual_max_ = y_min_ + n_rows_tiles_ * background_size_;
  rect_1_ = {x_min_, y_min_, 4, y_actual_max_ - y_min_};
  rect_2_ = {x_min_, y_actual_max_, x_actual_max_ - x_min_, 4};
  rect_3_ = {x_min_, y_min_, x_actual_max_ - x_min_, 4};
  rect_4_ = {x_actual_max_, y_min_, 4, y_actual_max_ - y_min_ + 4};

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
    auto x_pos = (x_min_ + (x_actual_max_ - x_min_) / 2);
    auto y_pos = (y_min_ + (y_actual_max_ - y_min_) / 2);

    FontManger::Instance()->RenderText("Game over!", 48, {255, 0, 0}, x_pos,
                                       y_pos - 150, true);
    FontManger::Instance()->RenderText("Press R to restart ", 32, {255, 0, 0},
                                       x_pos, y_pos - 100, true);
    FontManger::Instance()->RenderText("Press ESCAPE to go to main menu", 32,
                                       {255, 0, 0}, x_pos, y_pos + 50, true);
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

  if (player_->HitTail() || player_bounding_box.x < x_min_ ||
      player_bounding_box.x > x_actual_max_ || player_bounding_box.y < y_min_ ||
      player_bounding_box.y > y_actual_max_) {
    playing_ = false;
    SoundManger::Instance()->Play("game_over", false);
    SoundManger::Instance()->Pause("background_music");
  }
  SDL_Rect fruit_box = fruit_->GetBoundingBox();
  player_bounding_box.x += 5;
  player_bounding_box.y += 5;
  player_bounding_box.w -= 10;
  player_bounding_box.h -= 10;

  if (CheckCollisionRecs(player_bounding_box, fruit_box)) {
    SoundManger::Instance()->Play("bite", false);
    AddFruit();
    player_->IncrementTail();
    score_++;
  }
}

void Level::AddPlayer() {
  PlayerInfo p;
  auto player_params =
      LoaderParams(p.file_path, p.x, p.y, p.sprite_width, p.sprite_height,
                   "player", p.num_frames, p.animation_speed, p.dest_width,
                   p.dest_height, p.items_per_row);
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

  auto new_loc = player_->NewFruitLocation((x_actual_max_ - x_min_) - 40,
                                           (y_actual_max_ - y_min_) - 40);
  p.x = 20 + (x_min_ + new_loc.x);
  p.y = 20 + (y_min_ + new_loc.y);

  auto food_params =
      LoaderParams(p.file_path, p.x, p.y, p.sprite_width, p.sprite_height,
                   "food", p.num_frames, p.animation_speed, p.dest_width,
                   p.dest_height, p.items_per_row);
  fruit_ = std::make_unique<Food>(food_params);
}

void Level::ShowScore() const {

  std::string num_s = std::to_string(score_);
  std::string text = "Score \n" + num_s;
  int win_w = Application::Instance()->GetScreenWidth();
  int x_pos = win_w - 150;
  FontManger::Instance()->RenderText(text.c_str(), 48, {255, 255, 255}, x_pos,
                                     50);

  num_s = std::to_string(high_score_);
  text = "High \nscore \n" + num_s;
  FontManger::Instance()->RenderText(text.c_str(), 48, {255, 255, 255}, x_pos,
                                     250);

  std::stringstream stream;
  num_s = std::format("{:.2f}", current_time_ / 1000);

  text = "Time \n" + num_s;
  FontManger::Instance()->RenderText(text.c_str(), 48, {255, 255, 255}, x_pos,
                                     650);
}

void Level::DrawBackground() const {

  for (int x = 0; x < n_cols_tiles_; x++) {
    for (int y = 0; y < n_rows_tiles_; y++) {
      auto x1 = x_min_ + x * background_size_;
      auto y1 = y_min_ + y * background_size_;
      TextureManger::Instance()->DrawImageWithSize(
          "background_tile", x1, y1, background_size_, background_size_);
    }
  }
  SDL_SetRenderDrawColor(Application::Instance()->GetRenderer(), 0, 0, 0, 244);
  SDL_RenderFillRect(Application::Instance()->GetRenderer(), &rect_1_);
  SDL_RenderFillRect(Application::Instance()->GetRenderer(), &rect_2_);
  SDL_RenderFillRect(Application::Instance()->GetRenderer(), &rect_3_);
  SDL_RenderFillRect(Application::Instance()->GetRenderer(), &rect_4_);
}
bool Level::CheckCollisionRecs(SDL_Rect rect, SDL_Rect rect_1) {
  return ((rect.x < (rect_1.x + rect_1.w) && (rect.x + rect.w) > rect_1.x) &&
          (rect.y < (rect_1.y + rect_1.h) && (rect.y + rect.h) > rect_1.y));
}
