//
// Created by Matt on 2/07/2024.
//

#pragma once

#include <SDL2/SDL.h>

#include <memory>
#include <string>

#include "Core/Game.h"
struct ApplicationParameters {
    const char *title = "RaySnake";
    bool full_screen = false;
    int window_width = 1000;
    int window_height = 800;
};

class Application {

public:
    static Application *Instance() {
        if (!s_instance_) {
            s_instance_ = new Application();
        }

        return s_instance_;
    }

    ~Application() { delete s_instance_; }
    SDL_Renderer *GetRenderer() { return renderer_; }
    SDL_Window *GetWindow() { return window_; }

    int GetScreenWidth() { return screen_width_; }
    int GetScreenHeight() { return screen_height_; }

    void Run();
    static Application *s_instance_;

private:
    Application() = default;

    void Initialise();
    void Render();
    void Update();
    void Loop();
    void Clean();

    SDL_Color background_color_ = {
            249,
            123,
            54,
            255,
    };

    const ApplicationParameters params_ = ApplicationParameters();

    SDL_Window *window_;
    SDL_Renderer *renderer_;
    double last_frame_time_ = 0.0;
    Game *game_;
    int screen_height_;
    int screen_width_;
};
