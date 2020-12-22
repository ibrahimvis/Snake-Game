#include "menu.h"

Menu::Menu() {
  TTF_Init();
  font = TTF_OpenFont("../FreeMono.ttf", 32);

  color.push_back({0xff, 0x00, 0x00}); // red
  color.push_back({0xff, 0xff, 0xff}); // white

  for (auto c : color) {
    textSurface.emplace_back(TTF_RenderText_Solid(font, "Play", c));
    textSurface.emplace_back(TTF_RenderText_Solid(font, "Exit", c));
  }

  textW = textSurface[0]->w;
  textH = textSurface[0]->h;
}

Menu::~Menu() {}

int Menu::getIndex(TextState i) {

  int index;
  switch (i) {
  case TextState::exitS:
    index = 1;
    break;

  case TextState::playU:
    index = 2;
    break;

  case TextState::exitU:
    index = 3;
    break;

  default:
    index = 0;
    break;
  }

  return index;
}

SDL_Surface *Menu::getText(TextState state) {
  int i = getIndex(state);
  return textSurface[i];
}