//
// FontManger.h
// Created by Matt on 5/07/2024.
//
// This header file defines the FontManger class, which is responsible for
// managing fonts and rendering text in an SDL-based application. It uses the
// SDL_ttf library to handle font loading and text rendering.
//
// Class: FontManger
// ------------------
// A singleton class that provides functionality to render text using SDL_ttf.
// It maintains a map of loaded fonts to optimize font reuse and avoid redundant
// loading.
//
// Public Methods:
// ----------------
// - static FontManger *Instance():
//     Returns the singleton instance of the FontManger class. If the instance
//     does not exist, it creates one.
//
// - void RenderText(const char *text, int font_size, SDL_Color col, int pos_x,
// int pos_y, bool centered = false):
//     Renders the given text on the screen at the specified position with the
//     specified font size and color. Optionally, the text can be centered at
//     the given position.
//
// - ~FontManger():
//     Destructor for the FontManger class. Cleans up any allocated resources.
//
// Private Members:
// -----------------
// - FontManger():
//     Private constructor to enforce the singleton pattern.
//
// - std::map<int, TTF_Font *> font_map_:
//     A map that associates font sizes with their corresponding TTF_Font
//     objects. This allows efficient reuse of fonts of the same size.
//
// Static Members:
// ----------------
// - static FontManger *s_instance_:
//     A static pointer to the singleton instance of the FontManger class.
//

#pragma once

#include <SDL.h>

#include <SDL_ttf.h>
#include <map>
#include <memory.h>
#include <memory>

class FontManger {

public:
  static FontManger *Instance() {

    if (!s_instance_) {

      s_instance_ = std::unique_ptr<FontManger>(new FontManger());
    }
    return s_instance_.get();
  }

  void RenderText(const char *text, int font_size, SDL_Color col, int pos_x,

                  int pos_y, bool centered = false);

  ~FontManger();

private:
  FontManger() = default;
  static std::unique_ptr<FontManger> s_instance_;
  std::map<int, TTF_Font *> font_map_;
};
