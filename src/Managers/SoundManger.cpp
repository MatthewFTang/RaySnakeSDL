//
// Created by Matt on 15/07/2024.
//

#include "SoundManger.h"
#include <iostream>
SoundManger *SoundManger::s_instance_ = nullptr;

void SoundManger::Load(const std::string &file_path, const std::string &id,
                       const std::string &type) {
  if (!sound_map_.contains(id)) {
    if (type == "music") {
      Mix_Music *audio = Mix_LoadMUS(file_path.c_str());
      if (audio == nullptr) {
        std::cout << "couldn't load sound : " << file_path << std::endl;
      }
      sound_map_[id].music = audio;
      audio_type_[id] = SoundType::MUSIC;
    } else {
      Mix_Chunk *audio = Mix_LoadWAV(file_path.c_str());
      sound_map_[id].wav = audio;
      audio_type_[id] = SoundType::SOUND;
    }
  }
}
void SoundManger::Play(const std::string &id, bool loop) {
  int n_loops;
  if (loop) {
    n_loops = -1;
  } else {
    n_loops = 0;
  }
  if (audio_type_[id] == SoundType::MUSIC) {
    Mix_PlayMusic(sound_map_[id].music, n_loops);
  } else {
    Mix_PlayChannel(-1, sound_map_[id].wav, n_loops);
  }
  is_playing_[id] = true;
}
void SoundManger::Pause(const std::string &id) {
  Mix_PauseMusic();
  is_playing_[id] = false;
}
void SoundManger::Render() {
  // Nothing to do
}
void SoundManger::Clean() {
  for (auto &sound : sound_map_) {
    if (audio_type_[sound.first] == SoundType::MUSIC) {
      Mix_FreeMusic(sound.second.music);
    } else {
      Mix_FreeChunk(sound.second.wav);
    }
  }
  sound_map_.clear();
  is_playing_.clear();
}
SoundManger::SoundManger() { Mix_OpenAudio(22050, AUDIO_S16, 2, 4096); }
SoundManger::~SoundManger() { Mix_CloseAudio(); }
