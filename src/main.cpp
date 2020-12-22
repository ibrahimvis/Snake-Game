#include "SDL.h"
#include "controller.h"
#include "game.h"
#include "menu.h"
#include "renderer.h"
#include <iostream>

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;

  Menu menu;
  int selected = 0;
  bool running = true;
  bool gameplayRunning = false;
  Uint32 nextTime = SDL_GetTicks() + 30;

  while (running) {

    if (!gameplayRunning) {
      controller.HandleMenuInput(selected, running, gameplayRunning);
      renderer.renderMenu(selected, menu);
    } else {
      Game game(kGridWidth, kGridHeight, kScreenHeight, kScreenWidth);
      game.Run(controller, renderer, kMsPerFrame);
      std::cout << "Your Stats Are: \n";
      std::cout << "Score: " << game.GetScore() << "\n";
      std::cout << "Size: " << game.GetSize() << "\n";
      gameplayRunning = false;
    }

    Uint32 now = SDL_GetTicks();
    if (nextTime > now) {
      SDL_Delay(nextTime - now);
    }

    nextTime += 30;
  }

  std::cout << "Game has terminated successfully!\n";
  return 0;
}