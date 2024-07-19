//
// Created by Matt on 5/07/2024.
//

#pragma once
#include <string>
struct PlayerInfo {
    std::string file_path = "src/resources/assets/Bird.png";
    std::string id = "player";
    int animation_speed = 8;
    int x = 200;
    int y = 200;
    int sprite_height = 622;
    int sprite_width = 716;
    int items_per_row = 4;
    int num_frames = 8;
    int dest_height = 50;
    int dest_width = 50;
};

struct FoodInfo {
    std::string file_path = "src/resources/assets/Apple.png";
    std::string id = "food";
    int animation_speed = 8;
    int x = 400;
    int y = 800;
    int sprite_height = 32;
    int sprite_width = 32;
    int items_per_row = 17;
    int num_frames = 17;
    int dest_height = 50;
    int dest_width = 50;
};
