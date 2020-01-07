#include <complex>
#include "Fractal_Event.h"

Fractal_Event::Fractal_Event(Fractal_Creator &creator, SDL_Event &event) :
    _pCreator(&creator), _pEvent(&event) {}

bool Fractal_Event::deal()
{
  switch (_pEvent->type)
  {
    case SDL_QUIT:
      return true;
      break;

    case SDL_MOUSEBUTTONUP:
      {
        int x, y;
        SDL_GetMouseState(&x, &y);
        std::complex<double> trans = _pCreator->coordinateTrans(x, y) - _pCreator->orign();
        _pCreator->transform(trans, 2);
      }
      break;

    case SDL_MOUSEWHEEL:
      _pCreator->transform({0, 0}, _pEvent->wheel.y > 0 ? 1.2 : .8);
      break;
  }
}

SDL_Event *Fractal_Event::operator&()
{
  return _pEvent;
}
