/**
 * @class Game
 * @brief Represents the core game engine responsible for managing the game
 * loop, state, and resources.
 *
 * The Game class serves as the central hub for the application, handling the
 * game loop, rendering, updating game logic, and managing transitions between
 * menus and levels. It provides methods to start, update, render, and quit the
 * game, as well as utilities for managing game state and resources.
 *
 * Key responsibilities include:
 * - Managing the game loop and ensuring smooth execution.
 * - Handling transitions between menus and gameplay levels.
 * - Providing an interface for starting new games and setting difficulty
 * levels.
 * - Managing global resources and cleanup.
 *
 * The class also provides utility functions to check the running state of the
 * game and dynamically set the current menu.
 */

// Created by Matt on 2/07/2024.
//
#pragma once

#include <memory>

#include "Level.h"
#include "Menu/Menu.h"

class Game {
public:
  /**
   * @brief Constructs a new Game instance.
   */
  Game();

  /**
   * @brief Default destructor for the Game class.
   */
  ~Game() = default;

  /**
   * @brief Cleans up any global resources used by the game.
   */
  static void Clean();

  /**
   * @brief Renders the current game state to the screen.
   */
  void Render() const;

  /**
   * @brief Updates the game state, including logic and physics.
   */
  void Update();

  /**
   * @brief Starts the game loop.
   */
  void Play();

  /**
   * @brief Exits the game loop and performs cleanup.
   */
  void Quit();

  /**
   * @brief Checks if the game is currently running.
   * @return True if the game is running, false otherwise.
   */
  [[nodiscard]] bool GetRunning() const { return running_; }

  /**
   * @brief Sets the current menu to a new menu of type T.
   * @tparam T The type of the menu to set.
   */
  template <typename T> void SetMenu() { menu_ = std::make_shared<T>(*this); }

  /**
   * @brief Starts a new game with the specified difficulty.
   * @param difficulty The difficulty level for the new game.
   */
  void NewGame(GameDifficulty difficulty);

private:
  bool running_ = true; ///< Indicates whether the game is currently running.
  std::unique_ptr<Level> level_; ///< The current level being played.
  std::shared_ptr<Menu> menu_;   ///< The current menu being displayed.
};
