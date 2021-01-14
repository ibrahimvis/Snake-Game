#include "menu.h"

Menu::Menu() {
  TTF_Init();
  font = TTF_OpenFont("../FreeMono.ttf", 32);

  color.push_back({0xff, 0x00, 0x00}); // red
  color.push_back({0xff, 0xff, 0xff}); // white

  // here we are creating the menu with two colors each
  // one for red, and one for white
  for (auto c : color) {
    textSurface.emplace_back(TTF_RenderText_Solid(font, "Play", c));
    textSurface.emplace_back(TTF_RenderText_Solid(font, "Exit", c));
  }

  // one more text added to the vector
  textSurface.emplace_back(
      TTF_RenderText_Solid(font, "Your top scores!", color[1]));

  // assigning these two values so we can use them in the render function
  textW = textSurface[0]->w;
  textH = textSurface[0]->h;
}

Menu::~Menu() {
  for (auto text : textSurface) {
    SDL_FreeSurface(text);
  }

  for (auto text : textScores) {
    SDL_FreeSurface(text);
  }

  TTF_CloseFont(font);
  TTF_Quit();
}

// get index and get text are used for choosing what text to render
int Menu::getIndex(TextState i) {

  int index;
  switch (i) {
  case TextState::playS:
    index = 0;
    break;

  case TextState::exitS:
    index = 1;
    break;

  case TextState::playU:
    index = 2;
    break;

  case TextState::exitU:
    index = 3;
    break;

  case TextState::topScores:
    index = 4;
    break;
  }

  return index;
}

SDL_Surface *Menu::getText(TextState state) {
  int i = getIndex(state);
  return textSurface[i];
}

// for rendering the scores
std::vector<SDL_Surface *> Menu::getTextScores() { return textScores; }

// for updating the scores
void Menu::updateScores(std::vector<int> scores) {

  for (int i = 0; i < scores.size(); i++) {
    std::string str =
        "#" + std::to_string(i + 1) + ":   " + std::to_string(scores[i]);
    textScores.emplace_back(TTF_RenderText_Solid(font, str.c_str(), color[1]));
  }
}