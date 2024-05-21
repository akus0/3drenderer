#include "display.h"
#include "vector.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

vec3_t camera_position = {.x = 0, .y = 0, .z = -5};
vec3_t cube_rotation = {.x = 0, .y = 0, .z = 0};

float fov_factor = 640;

bool is_running = false;
int previous_frame_time = 0;

void setup(void) {
  // Allocate the required memory in bytes to hold the color buffer

  color_buffer =
      (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);

  // Creating a SDL texture that is used to display the color buffer
  color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                           SDL_TEXTUREACCESS_STREAMING,
                                           window_width, window_height);
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

///////////////////////////////////////////////////////////////////////////////
/// Function that receives a 3D vector and returns a projected 2D point
///////////////////////////////////////////////////////////////////////////////
vec2_t project(vec3_t point) {
  vec2_t projected_point = {
      .x = (fov_factor * point.x) / point.z,
      .y = (fov_factor * point.y) / point.z,
  };
  return projected_point;
}

void update(void) {

  // Wait some time until reach the tatget frame time in milliseconds
  int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

  // Only delay execution if we are running too fast
  if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
    SDL_Delay(time_to_wait);
  }

  previous_frame_time = SDL_GetTicks();

  cube_rotation.x += 0.01;
  cube_rotation.y += 0.01;
  cube_rotation.z += 0.01;

  // for (int i = 0; i < N_POINTS; i++) {
  //   vec3_t point = cube_points[i];
  //
  //   vec3_t transformed_point = vec3_rotate_x(point, cube_rotation.x);
  //   transformed_point = vec3_rotate_y(transformed_point, cube_rotation.y);
  //   transformed_point = vec3_rotate_z(transformed_point, cube_rotation.z);
  //
  //   // Translate the points away from the camera
  //   transformed_point.z -= camera_position.z;
  //
  //   // Project the current point
  //   vec2_t projected_point = project(transformed_point);
  //
  //   // Save the projected 2DR vector in the array of projected points
  //   projected_points[i] = projected_point;
  // }
}

void render(void) {
  draw_grid();
  //
  // // Loop all projected points and render them
  // for (int i = 0; i < N_POINTS; i++) {
  //   vec2_t projected_point = projected_points[i];
  //   draw_rect(projected_point.x + (window_width / 2),
  //             projected_point.y + (window_height / 2), 4, 4, 0xFFFFFF00);
  // }
  //
  render_color_buffer();
  clear_color_buffer(0x00000000);

  SDL_RenderPresent(renderer);
}

int main(void) {
  is_running = initialize_window();

  setup();

  // vec3_t myvector = {2.0, 3.0, -4.0};

  while (is_running) {
    process_input();
    update();
    render();
  }

  destroy_window();

  return 0;
}
