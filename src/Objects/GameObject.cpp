//
// Created by Matt on 3/07/2024.
//

#include "GameObject.h"

#include "Managers/TextureManger.h"

void GameObject::Render() {
    TextureManger::Instance()->DrawFrame(texture_id_,
                                         position_.x,
                                         position_.y,
                                         width_,
                                         height_,
                                         items_per_row_,
                                         current_frame_,
                                         rotation_,
                                         dest_height_,
                                         dest_width_);
}

void GameObject::Clean() {
    TextureManger::Instance()->DeleteTexture(texture_id_);
}
GameObject::GameObject(LoaderParams const &params)
    : position_(params.GetX(), params.GetY()),

      width_(params.GetWidth()),
      height_(params.GetHeight()),
      items_per_row_(params.GetItemsPerRow()),
      num_frames_(params.GetNumFrames()),
      dest_height_(params.GetDestHeight()),
      dest_width_(params.GetDestWidth()),
      animation_speed_(params.GetAnimateSpeed()),
      texture_id_(params.GetTextureId()) {
    bounding_box_.h = dest_height_;
    bounding_box_.w = dest_width_;
    TextureManger::Instance()->LoadText(params.GetFilePath(), texture_id_);
}

SDL_Rect GameObject::GetBoundingBox() {
    bounding_box_.x = position_.x;
    bounding_box_.y = position_.y;
    return bounding_box_;
}
