#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
public:
  void HandleInput(bool &running, bool &gameplayRunning, Snake &snake) const;
  void HandleMenuInput(int &selected, bool &running, bool &gameplayRunning) const;

private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif