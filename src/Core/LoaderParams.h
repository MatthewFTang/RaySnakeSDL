//
// Created by Matt on 5/07/2024.
//

#pragma once

#include <string>
#include <utility>

class LoaderParams {
public:
    LoaderParams(std::string file_path, int x, int y, int sprite_width,
                 int sprite_height, std::string id, int num_frames,
                 int animation_speed, int dest_width, int dest_height, int items_per_row)

        : file_path_(std::move(file_path)),
          x_(x),
          y_(y),
          width_(sprite_width),
          height_(sprite_height),
          num_frames_(num_frames),
          anim_speed_(animation_speed),
          dest_height_(dest_height),
          dest_width_(dest_width),
          items_per_row_(items_per_row),
          texture_id_(std::move(id)) {}

    [[nodiscard]] int GetX() const { return x_; }
    [[nodiscard]] int GetY() const { return y_; }
    [[nodiscard]] int GetWidth() const { return width_; }
    [[nodiscard]] int GetHeight() const { return height_; }
    [[nodiscard]] int GetNumFrames() const { return num_frames_; }
    [[nodiscard]] int GetAnimateSpeed() const { return anim_speed_; }
    [[nodiscard]] std::string GetTextureId() const { return &texture_id_[0]; }
    [[nodiscard]] std::string GetFilePath() const { return &file_path_[0]; }
    [[nodiscard]] int GetItemsPerRow() const { return items_per_row_; }
    [[nodiscard]] int GetDestHeight() const { return dest_height_; }
    [[nodiscard]] int GetDestWidth() const { return dest_width_; }

private:
    std::string file_path_;
    int x_;
    int y_;
    int width_;
    int height_;
    int num_frames_;
    int anim_speed_;
    int dest_height_;
    int dest_width_;
    int items_per_row_;
    std::string texture_id_;
};
