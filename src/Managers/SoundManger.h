
// SoundManger.h
//
//@brief Singleton class for managing audio resources in the application.
//
// Header file for the SoundManger class, a singleton responsible for managing
// audio resources in the application. This class provides functionality to
// load, play, pause, and clean up audio files, supporting both music and sound
// effects. It utilizes SDL_mixer for audio handling and maintains internal
// mappings for efficient resource management.
//
// Created by Matt on 15/07/2024.
//

#pragma once

#include <SDL_mixer.h>
#include <memory>
#include <string>
#include <unordered_map>

/**
 * @enum SoundType
 * @brief Enum to represent the type of audio.
 */
enum class SoundType {
  MUSIC, ///< Represents music files.
  SOUND  ///< Represents sound effect files.
};

/**
 * @struct audioTypes
 * @brief Struct to hold audio data.
 */
struct audioTypes {
  Mix_Music *music; ///< Pointer to music data.
  Mix_Chunk *wav;   ///< Pointer to sound effect data.
};

/**
 * @class SoundManger
 * @brief Singleton class to manage audio loading, playing, and cleanup.
 */
class SoundManger {

public:
  /**
   * @brief Static instance of the SoundManger class.
   */

  /**
   * @brief Get the singleton instance of SoundManger.
   * @return Pointer to the SoundManger instance.
   */
  static SoundManger *Instance() {
    if (!s_instance_) {
      s_instance_ = std::unique_ptr<SoundManger>(new SoundManger());
    }
    return s_instance_.get();
  };

  /**
   * @brief Load an audio file into memory.
   * @param file_path Path to the audio file.
   * @param id Identifier for the audio file.
   * @param type Type of the audio (MUSIC or SOUND).
   */
  void Load(const std::string &file_path, const std::string &id,
            const std::string &type);

  /**
   * @brief Play an audio file.
   * @param id Identifier of the audio file to play.
   * @param loop Whether the audio should loop (true) or play once (false).
   */
  void Play(const std::string &id, bool loop);

  /**
   * @brief Pause an audio file.
   * @param id Identifier of the audio file to pause.
   */
  void Pause(const std::string &id);

  /**
   * @brief Clean up all loaded audio resources.
   */
  void Clean();

  /**
   * @brief Destructor for the SoundManger class.
   */
  ~SoundManger();

private:
  /**
   * @brief Private constructor for the SoundManger class (singleton pattern).
   */
  SoundManger();
  static std::unique_ptr<SoundManger> s_instance_; ///< Singleton instance.
  std::unordered_map<std::string, audioTypes>
      sound_map_; ///< Map of audio IDs to audio data.
  std::unordered_map<std::string, SoundType>
      audio_type_; ///< Map of audio IDs to their types.
  std::unordered_map<std::string, bool>
      is_playing_; ///< Map of audio IDs to their playing state.
};
