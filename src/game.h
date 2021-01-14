#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "menu.h"

#include <random>

class Game {
public:
  
  Game(std::size_t grid_width, std::size_t grid_height,
       std::size_t screen_height, std::size_t screen_width);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

private:
  Snake snake;
  SDL_Point food;

  int numOfItems;
  std::vector<SDL_Point> items;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void placeFoodAndItems();
  void Update(bool &running);
};

#endif