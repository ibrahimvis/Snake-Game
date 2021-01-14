#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width), screen_height(screen_height),
      grid_width(grid_width), grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

////////////////////////////////////////////////////////////////////////////////////
// this is code works very similar to the to the render function
// here we use the menu reference to get the text to render
// and at what position to render it to
// also we check for the selected variable so we can change the color of 
// the highlighted text
////////////////////////////////////////////////////////////////////////////////////
void Renderer::renderMenu(int selected, Menu &menu, std::vector<int> scores) {
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  if (scores.size() > 0) {

    SDL_Surface *temp = menu.getText(Menu::TextState::topScores);

    SDL_Texture *text_texture;
    text_texture = SDL_CreateTextureFromSurface(
        sdl_renderer, temp);

    SDL_Rect dest;
    dest = {190, 290, temp->w, temp->h};

    SDL_RenderCopy(sdl_renderer, text_texture, NULL, &dest);

    try {
      renderScore(menu, scores);
    } catch (...) {
      
    }
  }

  if (selected == 0) {
    // color = {0xff, 0x00, 0x00};
    SDL_Texture *text_texture;
    text_texture = SDL_CreateTextureFromSurface(
        sdl_renderer, menu.getText(Menu::TextState::playS));

    SDL_Rect dest;
    dest = {290, 180, menu.getW(), menu.getH()};

    SDL_RenderCopy(sdl_renderer, text_texture, NULL, &dest);

    text_texture = SDL_CreateTextureFromSurface(
        sdl_renderer, menu.getText(Menu::TextState::exitU));

    dest = {290, 220, menu.getW(), menu.getH()};

    SDL_RenderCopy(sdl_renderer, text_texture, NULL, &dest);
  } else {
    // color = {0xff, 0x00, 0x00};
    SDL_Texture *text_texture;
    text_texture = SDL_CreateTextureFromSurface(
        sdl_renderer, menu.getText(Menu::TextState::playU));

    SDL_Rect dest;
    dest = {290, 180, menu.getW(), menu.getH()};

    SDL_RenderCopy(sdl_renderer, text_texture, NULL, &dest);

    text_texture = SDL_CreateTextureFromSurface(
        sdl_renderer, menu.getText(Menu::TextState::exitS));

    dest = {290, 220, menu.getW(), menu.getH()};

    SDL_RenderCopy(sdl_renderer, text_texture, NULL, &dest);
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::renderScore(Menu &menu, std::vector<int> scores) {

  int inc = 360;
  std::vector<SDL_Surface*> textScores = menu.getTextScores();

  for (int i = 0; i < textScores.size(); i++) {
    
    SDL_Texture *text_texture;
    text_texture = SDL_CreateTextureFromSurface(sdl_renderer, textScores[i]);

    SDL_Rect dest;
    dest = {250, inc, textScores[i]->w, textScores[i]->h};

    SDL_RenderCopy(sdl_renderer, text_texture, NULL, &dest);
    inc += 25;
  }
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) +
                    " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
