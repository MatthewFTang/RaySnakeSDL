//
// Created by Matt on 3/07/2024.
//

#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "Core/LoaderParams.h"
#include "Core/Vector2.h"

class GameObject {

 public:
  GameObject() = default;
  explicit GameObject(LoaderParams const &params);

  virtual ~GameObject() = default;

  virtual void Render();
  virtual void Clean();

  virtual void Update() = 0;
  virtual std::string GetGameObjectType() = 0;

  [[nodiscard]] Vector2 GetPosition() const { return position_; }
  [[nodiscard]] Vector2 GretAcceleration() const { return acceleration_; }
  [[nodiscard]] int GetWidth() const { return width_; }
  [[nodiscard]] int GetHeight() const { return height_; }
  [[nodiscard]] int GetNumFrames() const { return num_frames_; }
  [[nodiscard]] int GetFrameCount() const { return frame_count_; }
  [[nodiscard]] int GetCurrentFrame() const { return current_frame_; }
  [[nodiscard]] int GetDestWidth() const { return dest_width_; }
  [[nodiscard]] int GetDestHeight() const { return dest_height_; }
  std::string GetTextureId() { return &texture_id_[0]; }
  [[nodiscard]] int GetItemsPerRow() const { return items_per_row_; }
  [[nodiscard]] float GetRotation() const { return rotation_; }
  [[nodiscard]] int GetAnimationSpeed() const { return animation_speed_; }

  void SetPosition(Vector2 position) { position_ = position; }
  void SetVelocity(Vector2 velocity) { velocity_ = velocity; }
  void SetAcceleration(Vector2 acceleration) { acceleration_ = acceleration; }
  SDL_Rect GetBoundingBox();
  void SetRotation(float rot) { rotation_ = rot; }
  void SetCurrentFrame(int frame) { current_frame_ = frame; }

 private:
  Vector2 position_ = Vector2(0, 0);
  Vector2 velocity_ = Vector2(0, 0);
  Vector2 acceleration_ = Vector2(0, 0);
  SDL_Rect bounding_box_;
  float rotation_ = 0.0f;

  int width_;
  int height_;
  int items_per_row_;
  int num_frames_;
  int current_frame_ = 0;
  int frame_count_ = 0;
  int dest_height_;
  int dest_width_;
  int animation_speed_;
  std::string texture_id_;
};
