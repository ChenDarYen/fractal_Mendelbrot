#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL.h>

class Fractal_Creator;
class Screen
{
  friend class Fractal_Creator;
public:
  Screen(int width, int height);
  void update(const char *pPixels);
  ~Screen();

private:
  void _close();
  SDL_Window *_window;
  SDL_Renderer *_renderer;
  SDL_Texture *_texture;
};

#endif
