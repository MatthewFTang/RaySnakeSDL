//
// Created by Matt on 15/07/2024.
//

#include "SoundManger.h"
#include <iostream>
SoundManger *SoundManger::s_instance_ = nullptr;

void SoundManger::Load(const std::string &file_path, const std::string &id) {
  if (!sound_map_.contains(id)) {
	Mix_Music *music = Mix_LoadMUS(file_path.c_str());
        if (music== nullptr)
        {
          std::cout <<"couldn't load sound : " <<file_path<<std::endl;
        }
	sound_map_[id] = music;
  }
}
void SoundManger::Play(const std::string &id, bool loop) {
  int n_loops;
  if (loop) { n_loops = -1; }
  else { n_loops = 1; }
  Mix_PlayMusic(sound_map_[id], n_loops);
  is_playing_[id] = true;
}
void SoundManger::Pause(const std::string &id) {

  Mix_PauseMusic();
  is_playing_[id] = false;
}
void SoundManger::Render() {
//  for (auto const &[kId, kFlag] : is_playing_) {
//	if (kFlag && sound_map_[kId].type == SoundType::MUSIC) {
//	  Music temp = std::get<Music>(sound_map_[kId].data);
//	  UpdateMusicStream(temp);
//	}
//  }
}
void SoundManger::Clean() {
//
//  for (auto &[kName, kS] : sound_map_) {
//	if (kS.type == SoundType::MUSIC) {
//	  Music temp = std::get<Music>(kS.data);
//	  UnloadMusicStream(temp);
//	} else if (kS.type == SoundType::SOUND) {
//	  Sound temp = std::get<Sound>(kS.data);
//	  UnloadSound(temp);

//	}
//  }
  sound_map_.clear();
  is_playing_.clear();
}
SoundManger::SoundManger() {

  Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);

}
SoundManger::~SoundManger() {
  Mix_CloseAudio();

}
