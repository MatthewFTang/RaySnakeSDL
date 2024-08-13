//
// Created by Matt on 15/07/2024.
//

#pragma once

#include <SDL_mixer.h>
#include <string>
#include <unordered_map>

enum class SoundType { MUSIC, SOUND };
struct audioTypes {
  Mix_Music *music;
  Mix_Chunk *wav;
};

class SoundManger {

public:
  static SoundManger *s_instance_;

  static SoundManger *Instance() {
    if (s_instance_ == nullptr) {
      s_instance_ = new SoundManger();
    }
    return s_instance_;
  }

  void Load(const std::string &file_path, const std::string &id,
            const std::string &type);
  void Play(const std::string &id, bool loop);
  void Pause(const std::string &id);
  void Render();
  void Clean();
  ~SoundManger();

private:
  SoundManger();
  std::unordered_map<std::string, audioTypes> sound_map_;
  std::unordered_map<std::string, SoundType> audio_type_;
  std::unordered_map<std::string, bool> is_playing_;
};
