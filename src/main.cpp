#include "SDL.h"
#include "controller.h"
#include "game.h"
#include "menu.h"
#include "renderer.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////
// readScoresFromFile .. will load the user previous scores from previous games
// handleScores is for updating the scores vector
// writeScoresToFile will save the user scores to a file
////////////////////////////////////////////////////////////////////////////////////

std::vector<int> readScoresFromFile();
void handleScores(int score, std::vector<int> &scores);
void writeScoresToFile(std::vector<int> scores);

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;

  std::vector<int> scores = readScoresFromFile();

  Menu *menu = new Menu();
  menu->updateScores(scores);

  // for changing the text color
  int selected = 0;
  // will be true unless the user chooses to quit the game (will close the
  // window)
  bool running = true;
  // this will start the actual game if it is true
  bool gameplayRunning = false;
  Uint32 nextTime = SDL_GetTicks() + 30;

  while (running) {

    if (!gameplayRunning) {
      controller.HandleMenuInput(selected, running, gameplayRunning);
      renderer.renderMenu(selected, *menu, scores);
    } else {
      // to call the destrcutor
      delete menu;

      Game game(kGridWidth, kGridHeight, kScreenHeight, kScreenWidth);
      game.Run(controller, renderer, kMsPerFrame);
      std::cout << "Your Stats Are: \n";
      std::cout << "Score: " << game.GetScore() << "\n";
      std::cout << "Size: " << game.GetSize() << "\n";
      gameplayRunning = false;

      int score = game.GetScore();
      handleScores(score, scores);

      menu = new Menu();
      menu->updateScores(scores);
    }

    Uint32 now = SDL_GetTicks();
    if (nextTime > now) {
      SDL_Delay(nextTime - now);
    }

    nextTime += 30;
  }

  writeScoresToFile(scores);
  std::cout << "Game has terminated successfully!\n";
  return 0;
}

std::vector<int> readScoresFromFile() {
  std::ifstream file("../scoredb");
  std::string line;
  char key;
  int value;
  std::vector<int> scores;

  if (file.is_open()) {
    std::getline(file, line);

    std::istringstream iss(line);
    while (iss >> value >> key) {
      scores.emplace_back(value);
    }

    std::cout << std::endl;
  }
  file.close();

  return scores;
}

void writeScoresToFile(std::vector<int> scores) {
  std::fstream my_file;
  my_file.open("../scoredb", std::ios::out);

  if (scores.size()) {
    for (int i = 0; i < scores.size(); i++) {
      my_file << scores[i] << ",";
    }
  }

  my_file.close();
}

void handleScores(int score, std::vector<int> &scores) {
  if (score != 0) {
    if (scores.size() == 0) {
      scores.emplace_back(score);
    }

    else if (scores.size() < 5) {
      scores.emplace_back(score);

      std::sort(scores.begin(), scores.end(),
                [](int a, int b) { return a > b; });
      scores.erase(std::unique(scores.begin(), scores.end()), scores.end());
    }

    else if (score > scores[scores.size() - 1]) {
      scores.emplace_back(score);

      std::sort(scores.begin(), scores.end(),
                [](int a, int b) { return a > b; });
      scores.erase(std::unique(scores.begin(), scores.end()), scores.end());

      int size;
      if (scores.size() > 5)
        scores.resize(5);
    }
  }
}