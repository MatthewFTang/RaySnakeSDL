//
// Created by Matt on 5/07/2024.
//

#include "FontManger.h"

#include <Core/Application.h>

#include "Core/Vector2.h"
FontManger *FontManger::s_instance_ = nullptr;

void FontManger::RenderText(const char *text, int font_size, SDL_Color col, int pos_x, int pos_y, bool centered) {

    if (!font_map_.contains(font_size)) {
        font_map_[font_size] = TTF_OpenFont("src/resources/fonts/Lato-Bold.ttf", font_size);
    }

    Vector2 pos{pos_x, pos_y};


    SDL_Surface *text_surface = TTF_RenderUTF8_Blended_Wrapped
        (font_map_[font_size], text, {0, 0, 0},0);
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(Application::Instance()->GetRenderer(), text_surface);

    if (centered) {
        pos.x -= text_surface->w / 2;
        pos.y -= text_surface->h / 2;
    }
    Vector2 pos_shadow = pos;
    pos_shadow.x += 2;
    pos_shadow.y += 2;

    SDL_Rect src_rect = {0, 0, text_surface->w, text_surface->h};
    SDL_Rect dest_rect = {pos_shadow.x, pos_shadow.y, text_surface->w, text_surface->h};
    SDL_RenderCopy(Application::Instance()->GetRenderer(), text_texture, &src_rect, &dest_rect);

    text_surface = TTF_RenderUTF8_Blended_Wrapped(font_map_[font_size], text,
                                                  col,0);
    text_texture = SDL_CreateTextureFromSurface(Application::Instance()->GetRenderer(), text_surface);
    src_rect = {0, 0, text_surface->w, text_surface->h};
    dest_rect = {pos.x, pos.y, text_surface->w, text_surface->h};


    SDL_RenderCopy(Application::Instance()->GetRenderer(), text_texture, &src_rect, &dest_rect);
}
FontManger::~FontManger() {
    for (auto const &[kSize, kFont]: font_map_) {
        TTF_CloseFont(kFont);
    }
    font_map_.clear();
    TTF_Quit();
}
