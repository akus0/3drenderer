#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

SDL_Window *window;
SDL_Renderer *renderer;

bool initialize_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderrm "Error initializing SDL. \n");
    return false;
  }

  window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       800, 600, SDL_WINDOW_BORDERLESS);
  if (!window) {
    fprintf(stderr, "Error creating SDL window. \m");
    return false;

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
      fprintf(stderr, "Error creating renderer");
    }
    return true;
  }

  int main(void) {

    initialize_window();

    return 0;
  }
