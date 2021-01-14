#ifndef MENU_H
#define MENU_H

#include "SDL.h"
#include "SDL2/SDL_ttf.h"
#include "memory"
#include "vector"
#include <string>

class Menu {

public:
  Menu();
  ~Menu();
  enum class TextState { playS, exitS, playU, exitU, topScores };

  SDL_Surface *getText(TextState state);

  int getW() const { return textW; }
  int getH() const { return textH; }

  TTF_Font *getFont();

  std::vector<SDL_Surface*> getTextScores();
  void updateScores(std::vector<int> scores);

private:
  int getIndex(TextState i);
  TTF_Font *font;
  std::vector<SDL_Surface*> textSurface;
  std::vector<SDL_Surface*> textScores;
  std::vector<SDL_Color> color;
  int textW, textH;
  const int numOfMenu = 2;
};

#endif