#include "controller.h"
#include "SDL.h"
#include "snake.h"
#include <iostream>

void Controller::HandleMenuInput(int &selected, bool &running,
                                 bool &gameplayRunning) const {
  SDL_Event e;

  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
      case SDLK_UP:
      case SDLK_DOWN:
        selected = (selected == 1) ? 0 : 1;
        break;

      case SDLK_RETURN:
        if (selected == 0)
          gameplayRunning = true;
        else
          running = false;
        // std::cout << "Enter Pressed!" << std::endl;
        break;
      }
    }
  }
}

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1)
    snake.direction = input;
  return;
}

void Controller::HandleInput(bool &running, bool &gameplayRunning,
                             Snake &snake) const {
  SDL_Event e;

  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
      gameplayRunning = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
      case SDLK_UP:
        ChangeDirection(snake, Snake::Direction::kUp, Snake::Direction::kDown);
        break;

      case SDLK_DOWN:
        ChangeDirection(snake, Snake::Direction::kDown, Snake::Direction::kUp);
        break;

      case SDLK_LEFT:
        ChangeDirection(snake, Snake::Direction::kLeft,
                        Snake::Direction::kRight);
        break;

      case SDLK_RIGHT:
        ChangeDirection(snake, Snake::Direction::kRight,
                        Snake::Direction::kLeft);
        break;
      }
    }
  }

  // this block of code is used so we can now if the user is holding
  // the key .. if so we increase the movment speed of the snake
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  if (state[SDL_SCANCODE_UP] && snake.direction == Snake::Direction::kUp) {
    snake.speed = 0.3f;
  } else if (state[SDL_SCANCODE_RIGHT] &&
             snake.direction == Snake::Direction::kRight) {
    snake.speed = 0.3f;
  } else if (state[SDL_SCANCODE_LEFT] &&
             snake.direction == Snake::Direction::kLeft) {
    snake.speed = 0.3f;
  } else if (state[SDL_SCANCODE_DOWN] &&
             snake.direction == Snake::Direction::kDown) {
    snake.speed = 0.3f;
  } else {
    snake.speed = 0.1f;
  }
}