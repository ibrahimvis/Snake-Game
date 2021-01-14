#include "game.h"
#include "SDL.h"
#include <iostream>

Game::Game(std::size_t grid_width, std::size_t grid_height,
           std::size_t screen_height, std::size_t screen_width)
    : snake(grid_width, grid_height), engine(dev()),
      random_w(0, static_cast<int>(screen_width / grid_width)),
      random_h(0, static_cast<int>(screen_height / grid_height)) {

  // number of items reflect how many red squares
  numOfItems = 5;
  placeFoodAndItems();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {

  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;

  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render
    // this part is for the gameplay.
    controller.HandleInput(running, snake);
    Update(running);

    // we added items with food and snake 
    // so we can render them
    renderer.Render(snake, food, items);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::placeFoodAndItems() {
  int x, y;
  items.clear();
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;

      break;
    }
  }


  // check the point is not occupied we place the item 
  bool check = true;
  for (int i = 0; i < numOfItems; i++) {
    while (true) {
      x = random_w(engine);
      y = random_h(engine);

      if (x != food.x && y != food.y) {

        if (!snake.SnakeCell(x, y)) {
          if (i > 0) {
            check = true;
            for (int j = i; j >= 0; j--) {
              if (x == items[j].x && items[j].y == y) {
                check = false;
                break;
              }
            }
          }

          if (check) {
            SDL_Point temp{x, y};
            items.emplace_back(temp);
            check = false;
            break;
          }
        }
      }
    }
  }
}

void Game::Update(bool &running) {

  if (!snake.alive) {
    running = false;
    return;
  }

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // check if the snake eat one of the red squares
  for (auto i : items) {
    if (i.x == new_x && i.y == new_y) {
      snake.alive = false;
      running = false;
      return;      
    }
  }

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    placeFoodAndItems();
    // Grow snake and increase speed.
    snake.GrowBody();

  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }