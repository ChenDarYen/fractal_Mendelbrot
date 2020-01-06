#include <iostream>
#include <stdexcept>
#include <cstdint>
#include <SDL.h>
#include "Bitmap.cpp"
#include "Screen.cpp"
#include "RGB.cpp"
#include "Zoom_List.cpp"
#include "Mandelbrot.cpp"
#include "Fractal_Creator.cpp"

using std::cerr;
using std::endl;
using std::uint32_t;

int main()
{
  const int WIDTH = 1056, HEIGHT = 600;
  const double STD_SCALE = std::min(WIDTH, HEIGHT) / 2.3;

  try
  {
    Fractal_Creator fractal_creator(WIDTH, HEIGHT, STD_SCALE * .8, 500);

    fractal_creator.addZoom({-0.5, 0}, STD_SCALE);

    fractal_creator.addGrad(0, RGB(0, 0, 40));
    fractal_creator.addGrad(0.4, RGB(0, 0, 50));
    fractal_creator.addGrad(0.7, RGB(10, 10, 60));
    fractal_creator.addGrad(0.9, RGB(80, 90, 60));
    fractal_creator.addGrad(0.95, RGB(140, 140, 70));
    fractal_creator.addGrad(0.97, RGB(180, 70, 70));
    fractal_creator.addGrad(0.98, RGB(200, 0, 0));
    fractal_creator.addGrad(0.999, RGB(180, 100, 100));
    fractal_creator.addGrad(1, RGB(200, 0, 0));

    SDL_Event event;
    bool quit = false;

    while(!quit)
    {
      fractal_creator.updateScreen();

      while(SDL_PollEvent(&event))
      {
        switch(event.type)
        {
          case SDL_QUIT:
            quit = true;
            break;

          case SDL_MOUSEBUTTONUP:
            {
              int x, y;
              SDL_GetMouseState(&x, &y);
              std::complex<double> trans = fractal_creator.coordinateTrans(x, y) - fractal_creator.orign();
              fractal_creator.transform(trans, 2);
            }
            break;

          case SDL_MOUSEWHEEL:
            fractal_creator.transform({0, 0}, event.wheel.y > 0 ? 1.2 : .8);
            break;
        }
      }
    }
  }
  catch(Screen_Exception &e)
  {
    cerr << "Screen_Exception: " << e.what() << endl;
  }
  catch(std::exception &e)
  {
    cerr << e.what() << endl;
  }

  SDL_Quit();

  return 0;
}
