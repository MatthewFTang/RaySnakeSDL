//
// Created by Matt on 5/07/2024.
//

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <map>

class FontManger {
public:
  static FontManger *s_instance_;

  static FontManger *Instance() {
    if (s_instance_ == nullptr) {
      s_instance_ = new FontManger();
      return s_instance_;
    }
    return s_instance_;
  }
  void RenderText(const char *text, int font_size, SDL_Color col, int pos_x,
                  int pos_y, bool centered = false);

  ~FontManger();

private:
  FontManger() = default;
  std::map<int, TTF_Font *> font_map_;
};
