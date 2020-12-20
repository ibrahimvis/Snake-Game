#ifndef MENU_H
#define MENU_H

#include "SDL.h"
#include "SDL2/SDL_ttf.h"
#include "memory"
#include "vector"

class Menu {
  enum class Color { kWhite, kRed };

private:
  std::vector<SDL_Surface> menus;
  SDL_Color color = {0, 0, 0}, bgcolor = {0xff, 0xff, 0xff};
  TTF_Font *font;
  int selected;

public:
  Menu(std::size_t screen_width, std::size_t screen_height);
  ~Menu();
};

#endif