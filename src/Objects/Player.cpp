//
// Created by Matt on 3/07/2024.
//

#include "Player.h"

#include <cmath>
#include <random>

#include "Managers/InputManager.h"
#include "Managers/TextureManger.h"

void Player::Update() {
  if (InputManager::Instance()->IsKeyPress(SDLK_DOWN) ||
      InputManager::Instance()->IsKeyPress(SDLK_s)) {
    pos_accum_.y += 1;
    input_this_frame_ = true;
  }

  if (InputManager::Instance()->IsKeyPress(SDLK_UP) ||
      InputManager::Instance()->IsKeyPress(SDLK_w)) {
    pos_accum_.y -= 1;
    input_this_frame_ = true;
  }
  if (InputManager::Instance()->IsKeyPress(SDLK_LEFT) ||
      InputManager::Instance()->IsKeyPress(SDLK_a)) {
    pos_accum_.x -= 1;
    input_this_frame_ = true;
  }
  if (InputManager::Instance()->IsKeyPress(SDLK_RIGHT) ||
      InputManager::Instance()->IsKeyPress(SDLK_d)) {
    pos_accum_.x += 1;
    input_this_frame_ = true;
  }

  frame_counter_++;
  UpdatePosition();
  int cur_frame = GetCurrentFrame();
  if (frame_counter_ == GetAnimationSpeed()) {
    frame_counter_ = 0;
    cur_frame++;
    if (cur_frame == GetNumFrames())
      cur_frame = 0;
    SetCurrentFrame(cur_frame);
  }
}
void Player::UpdatePosition() {

  if (input_this_frame_) {
    current_angle_ = atan2(pos_accum_.y, pos_accum_.x);
    current_angle_deg_ = static_cast<float>(current_angle_ * 180 / M_PI);
    current_angle_deg_ = fmod(current_angle_deg_, 360.0);
    SetRotation(current_angle_deg_);
  }
  input_this_frame_ = false;

  auto dx = (int)std::round(movement_speed_ * std::cos(current_angle_));
  auto dy = (int)std::round(movement_speed_ * std::sin(current_angle_));

  pos_accum_.x = pos_accum_.y = 0;
  Vector2 pos = GetPosition();
  pos.x += dx;
  pos.y += dy;

  SetPosition(pos);
  UpdateTail();
}

void Player::UpdateTail() {

  auto number_pos_needed =
      (int)std::floor(frames_to_jump_back_one_ * (float)current_length_ - 1);
  tail_positions_[0] = GetPosition();

  int size_squared = (GetDestWidth() * GetDestWidth());

  for (int i = number_pos_needed; i > 0; i--) {
    tail_positions_[i] = tail_positions_[i - 1];
    rotation_positions_[i] = rotation_positions_[i - 1];
  }
  rotation_positions_[0] = GetRotation();

  for (int i = 0; i < current_length_; i++) {
    auto new_ind = static_cast<int>(
        std::floor(frames_to_jump_back_one_ * static_cast<float>(i)));
    tail_[i] = tail_positions_[new_ind];
    if (i > 1) {
      int dist = tail_[0].DistanceSquared(tail_[i]);
      if (dist < size_squared) {
        is_dead_ = true;
      }
    }

    tail_rotations_[i] = rotation_positions_[new_ind];
  }
}
void Player::IncrementTail() { current_length_++; }
void Player::Render() {
  std::string texture_id = GetTextureId();

  int current_frame = GetCurrentFrame();

  for (int i = 0; i < current_length_; i++) {
    TextureManger::Instance()->DrawFrame(
        texture_id, tail_[i].x, tail_[i].y, width, height, items_per_row,
        current_frame, tail_rotations_[i], dest_height, dest_width);
    current_frame++;
    if (current_frame == GetNumFrames())
      current_frame = 0;
  }
}
void Player::NewGame() {
  current_length_ = 1;

  frames_to_jump_back_one_ = (float)GetDestWidth() / movement_speed_;
  tail_.clear();
  rotation_positions_.clear();

  tail_.reserve(256);
  tail_rotations_.reserve(256);
  for (int i = 0; i < 256; i++) {
    tail_.push_back({0, 0});
    tail_rotations_.push_back(0.0f);
  }
  tail_positions_.clear();
  tail_positions_.reserve(256 * 6);
  rotation_positions_.reserve(256 * 6);

  for (int i = 0; i < 256 * 6; i++) {
    tail_positions_.push_back({0, 0});
    rotation_positions_.push_back(0.0f);
  }
  is_dead_ = false;

  dest_height = GetDestHeight();
  dest_width = GetDestWidth();
  width = GetWidth();
  height = GetHeight();
  items_per_row = GetItemsPerRow();
}

Vector2 Player::NewFruitLocation(int width_max, int height_max) {
  auto temp_x = GetRandomValue(0, width_max);
  auto temp_y = GetRandomValue(0, height_max);
  if (current_length_ > 1) {
    auto size_squared = GetDestWidth();
    size_squared *= size_squared;
    int number_pos_needed =
        std::floor(frames_to_jump_back_one_ * current_length_ - 1);
    Vector2 temp_vector = {temp_x, temp_y};

    for (int b = 0; b < number_pos_needed; b++) {
      const int dist = temp_vector.DistanceSquared(tail_positions_[b]);
      if (dist < size_squared) {
        temp_x = GetRandomValue(0, width_max);
        temp_y = GetRandomValue(0, height_max);
        temp_vector = {temp_x, temp_y};
        b = 0;
      }
    }
  }

  return {temp_x, temp_y};
}
int Player::GetRandomValue(int i, int max) {

  return (int)(i + (rand() / (RAND_MAX + 1.0)) * max);
}
