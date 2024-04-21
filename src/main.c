#include "display.h"
#include "vector.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
/// Declare an array of vectors/pointsx
///////////////////////////////////////////////////////////////////////////////
const int N_POINTS = 9 * 9 * 9;
vec3_t cube_points[N_POINTS]; // 9x9x9 cube

bool is_running = false;

void setup(void) {
  // Allocate the required memory in bytes to hold the color buffer

  color_buffer =
      (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);

  // Creating a SDL texture that is used to display the color buffer
  color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                           SDL_TEXTUREACCESS_STREAMING,
                                           window_width, window_height);

  int point_count = 0;

  // Start loading my array of vectors
  // from -1 to 1 (in this 9x9x9 cube)
  for (float x = -1; x <= 1; x += 0.25) {
    for (float y = -1; y <= 1; y += 0.25) {
      for (float z = -1; z <= 1; z += 0.25) {
        vec3_t new_point = {.x = x, .y = y, .z = z};
        cube_points[point_count++] = new_point;
      }
    }
  }
}

void process_input(void) {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    is_running = false;
    break;
  case SDL_KEYDOWN:
    if (event.key.keysym.sym == SDLK_ESCAPE)
      is_running = false;
    break;
  }
}
void update(void) {}

void render(void) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  draw_grid();

  draw_pixel(800, 50, 0xFFFFFFFF);
  draw_rect(100, 200, 100, 700, 0xFF333333);
  render_color_buffer();
  clear_color_buffer(0x00000000);

  SDL_RenderPresent(renderer);
}

int main(void) {
  is_running = initialize_window();

  setup();

  vec3_t myvector = {2.0, 3.0, -4.0};

  while (is_running) {
    process_input();
    update();
    render();
  }

  destroy_window();

  return 0;
}
