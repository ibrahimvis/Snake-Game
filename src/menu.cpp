#include "menu.h"

Menu::Menu(std::size_t screen_width, std::size_t screen_height) {
  font = TTF_OpenFont("font.ttf", 16);
  menus.emplace_back(TTF_RenderText_Shaded(font, "Play", color, bgcolor));
  menus.emplace_back(TTF_RenderText_Shaded(font, "Exit", color, bgcolor));
  selected = 0;
}

Menu::~Menu() {
  for (auto m : menus) {
      SDL_FreeSurface(&m);
  }
}