#include "Screen.h"
#include "Screen_Exception.h"

Screen::Screen(int width, int height)
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
    throw Screen_Exception("SDL init failed.");

  _window = SDL_CreateWindow("fracral",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      width, height,
      SDL_WINDOW_SHOWN);
  if(_window == nullptr)
  {
    _close();
    throw Screen_Exception(SDL_GetError());
  }

  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);
  if(_renderer == nullptr)
  {
    _close();
    throw Screen_Exception(SDL_GetError());
  }

  _texture = SDL_CreateTexture(_renderer,
      SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STATIC,
      width, height);
  if(_texture == nullptr)
  {
    _close();
    throw Screen_Exception(SDL_GetError());
  }
}
  
void Screen::update(const char *pPixels)
{
  int width;
  SDL_GetWindowSize(_window, &width, NULL);

  SDL_UpdateTexture(_texture, NULL, pPixels, width * 3);
  SDL_RenderClear(_renderer);
  SDL_RenderCopy(_renderer, _texture, NULL, NULL);
  SDL_RenderPresent(_renderer);
}

Screen::~Screen()
{
  SDL_DestroyTexture(_texture);
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);
}

void Screen::_close()
{
  SDL_DestroyTexture(_texture);
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);
  SDL_Quit();
}
