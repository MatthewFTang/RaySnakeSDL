//
// Created by Matt on 15/07/2024.
//

#pragma once

#include <unordered_map>
#include <string>
#include <variant>
#include <SDL2_mixer/SDL_mixer.h>

enum class SoundType {
  MUSIC,
  SOUND
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

  void Load(const std::string &file_path, const std::string &id);
  void Play(const std::string &id, bool loop);
  void Pause(const std::string &id);
  void Render();
  void Clean();
  ~SoundManger();

 private:
  SoundManger();
  std::unordered_map<std::string, Mix_Music *> sound_map_;
  std::unordered_map<std::string, bool> is_playing_;
};
