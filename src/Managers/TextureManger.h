//
// TextureManger.h
//
// Created by Matt on 5/07/2024.
//
// This header file defines the `TextureManger` class, a singleton responsible
// for managing textures in an SDL-based application. The `TextureManger` class
// provides functionality to load, draw, and manage textures efficiently,
// ensuring that textures are reused and properly cleaned up when no longer
// needed. It also supports advanced operations such as drawing frames from
// sprite sheets and retrieving texture dimensions.
//
// Usage:
// - Use `TextureManger::Instance()` to access the singleton instance.
// - Load textures using `LoadText()` and manage them with the provided methods.
// - Ensure proper cleanup by calling `CleanAll()` before application
// termination.
//

#pragma once

#include "Core/Vector2.h"
#include <SDL.h>
#include <memory>
#include <string>
#include <unordered_map>

/**
 * @class TextureManger
 * @brief A singleton class for managing SDL textures.
 *
 * The `TextureManger` class provides methods to load, draw, and manage textures
 * in an SDL-based application. It ensures efficient texture reuse and proper
 * cleanup to optimize resource usage.
 */
class TextureManger {
public:
  /**
   * @brief Get the singleton instance of the TextureManger.
   * @return A pointer to the singleton instance.
   */
  static TextureManger *Instance() {
    if (!s_instance_) {
      s_instance_ = std::unique_ptr<TextureManger>(new TextureManger);
    }
    return s_instance_.get();
  }

  /**
   * @brief Load a texture from a file and associate it with an ID.
   * @param file_name The path to the texture file.
   * @param id The unique identifier for the texture.
   */
  void LoadText(std::string const &file_name, std::string const &id);

  /**
   * @brief Draw a texture on the screen using its ID.
   * @param id The unique identifier of the texture to draw.
   */
  void DrawImage(const std::string &id);

  /**
   * @brief Draw a texture with specified size and location.
   * @param id The unique identifier of the texture to draw.
   * @param x_location The x-coordinate of the destination.
   * @param y_location The y-coordinate of the destination.
   * @param height The height of the destination rectangle.
   * @param width The width of the destination rectangle.
   */
  void DrawImageWithSize(const std::string &id, int x_location, int y_location,
                         int height, int width);

  /**
   * @brief Draw a specific frame from a sprite sheet.
   * @param id The unique identifier of the texture.
   * @param x_offset The x-coordinate offset in the sprite sheet.
   * @param y_offset The y-coordinate offset in the sprite sheet.
   * @param width The width of a single frame.
   * @param height The height of a single frame.
   * @param items_per_row The number of frames per row in the sprite sheet.
   * @param current_frame The index of the frame to draw.
   * @param rotation The rotation angle in degrees.
   * @param dest_height The height of the destination rectangle.
   * @param dest_width The width of the destination rectangle.
   */
  void DrawFrame(const std::string &id, int x_offset, int y_offset, int width,
                 int height, int items_per_row, int current_frame,
                 float rotation, int dest_height, int dest_width);

  /**
   * @brief Delete a texture from the manager.
   * @param id The unique identifier of the texture to delete.
   */
  void DeleteTexture(const std::string &id);

  /**
   * @brief Clean up all loaded textures.
   */
  void CleanAll();

  /**
   * @brief Get the dimensions of a texture.
   * @param id The unique identifier of the texture.
   * @return A `Vector2` object containing the width and height of the texture.
   */
  [[nodiscard]] Vector2 GetTextureDimensions(const std::string &id);

  ~TextureManger() = default;

private:
  /**
   * @brief Private constructor to enforce singleton pattern.
   */
  TextureManger() = default;

  /// A static pointer to the singleton instance.
  static std::unique_ptr<TextureManger> s_instance_;

  /// A map storing textures associated with their unique identifiers.
  std::unordered_map<std::string, SDL_Texture *> texture_map_;
};
