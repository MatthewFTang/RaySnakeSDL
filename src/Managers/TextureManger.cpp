//
// Created by Matt on 5/07/2024.
//

#include "TextureManger.h"

#include <SDL2_image/SDL_image.h>

#include <filesystem>
#include <iostream>

#include "Core/Application.h"
TextureManger *TextureManger::s_instance_ = nullptr;

void TextureManger::LoadText(std::string const &file_name, std::string const &id) {
    if (!texture_map_.contains(id)) {
        if (std::filesystem::exists(file_name)) {
            SDL_Surface *temp_surface = IMG_Load(file_name.c_str());
            SDL_Texture *temp_texture = SDL_CreateTextureFromSurface(Application::Instance()->GetRenderer(), temp_surface);
            SDL_FreeSurface(temp_surface);
            if (temp_texture != nullptr)
                texture_map_[id] = temp_texture;
            else
                std::cout << "TextureManger :: File (" << file_name << ") error" << std::endl;
        }
    }
}
void TextureManger::DrawImage(const std::string &id) {

    int h = Application::Instance()->GetScreenHeight();
    int w = Application::Instance()->GetScreenWidth();
    SDL_Rect src_rect;
    SDL_Rect dest_rect;

    Vector2 text_size = GetTextureDimensions(id);
    src_rect.x = src_rect.y = 0;
    src_rect.w = text_size.x;
    src_rect.h = text_size.y;
    dest_rect.x = dest_rect.y = 0;
    dest_rect.w = w;
    dest_rect.h = h;
    SDL_RenderCopyEx(Application::Instance()->GetRenderer(), texture_map_[id], &src_rect, &dest_rect, 0, nullptr,
                     SDL_RendererFlip::SDL_FLIP_NONE);
}

void TextureManger::DrawImageWithSize(const std::string &id,
                                      int x_location,
                                      int y_location,
                                      int height,
                                      int width) {
    Vector2 text_size = GetTextureDimensions(id);
    SDL_Rect src_rect;
    SDL_Rect dest_rect;
    src_rect.x = src_rect.y = 0;
    src_rect.w = text_size.x;
    src_rect.h = text_size.y;

    dest_rect.x = x_location;
    dest_rect.y = y_location;
    dest_rect.w = height;
    dest_rect.h = width;
    SDL_RenderCopyEx(Application::Instance()->GetRenderer(), texture_map_[id], &src_rect, &dest_rect, 0, nullptr,
                     SDL_FLIP_NONE);
}

void TextureManger::CleanAll() {
    for (auto const &[kId, kText]: texture_map_) {
        SDL_DestroyTexture(texture_map_[kId]);
    }
    texture_map_.clear();
}
void TextureManger::DrawFrame(const std::string &id, int x_offset, int y_offset,
                              int width, int height, int items_per_row,
                              int current_frame, float rotation, int dest_height, int dest_width) {

    SDL_Rect dest_rect;
    SDL_Rect src_rect;

    src_rect.x = (width * (current_frame % items_per_row));
    src_rect.y = (height * (current_frame / items_per_row));

    src_rect.h = height;
    src_rect.w = width;

    dest_rect.h = dest_height;
    dest_rect.w = dest_width;
    dest_rect.x = x_offset;
    dest_rect.y = y_offset;

    Vector2 o{dest_height / 2, dest_width / 2};
    SDL_RendererFlip flip;

    if (rotation > 90 && rotation < 270) {
        flip = SDL_FLIP_HORIZONTAL;
    } else {
        flip = SDL_FLIP_NONE;
    }
    SDL_RenderCopyEx(Application::Instance()->GetRenderer(),
                     texture_map_[id],
                     &src_rect,
                     &dest_rect,
                     rotation,
                     nullptr,
                     flip);
}
void TextureManger::DeleteTexture(const std::string &id) {

    SDL_DestroyTexture(texture_map_[id]);
    texture_map_.erase(id);
}

Vector2 TextureManger::GetTextureDimensions(const std::string &id) {
    int text_size_w = 0;
    int text_size_h = 0;                              // Declare variables to hold the size
    if (texture_map_.find(id) != texture_map_.end()) {// Check if the texture exists
        SDL_Texture *texture = texture_map_[id];
        if (SDL_QueryTexture(texture, nullptr, nullptr, &text_size_w, &text_size_h) == 0) {// Successfully queried texture size
            return Vector2{text_size_w, text_size_h};                                      // Return dimensions as Vector2
        } else {
            std::cerr << "SDL_QueryTexture error: " << SDL_GetError() << '\n';
        }
    } else {
        std::cerr << "Texture ID not found: " << id << '\n';
    }
    return Vector2{0, 0};// Return default Vector2 in case of failure
}