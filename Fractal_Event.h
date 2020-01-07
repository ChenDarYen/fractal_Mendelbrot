#ifndef FRACTAL_EVENT_H_
#define FRACTAL_EVENT_H_

#include <SDL.h>
#include "Fractal_Creator.h"

class Fractal_Event
{
public:
  Fractal_Event(Fractal_Creator &creator, SDL_Event &event);
  bool deal();
  SDL_Event *operator&();
  
private:
  Fractal_Creator *_pCreator;
  SDL_Event *_pEvent;
};

#endif
