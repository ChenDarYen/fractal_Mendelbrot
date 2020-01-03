#include "Zoom_List.h"
#include "Zoom.h"

void Zoom_List::push(const Zoom &zoom)
{
  _zooms.push_back(zoom);
}

void Zoom_List::push(std::complex<double> translate, double scale)
{
  Zoom zoom;
  zoom.translate = translate;
  zoom.scale = scale;
  push(zoom);
} 

void Zoom_List::pop()
{
  _zooms.pop_back();
}

Zoom &Zoom_List::top()
{
  return _zooms.back();
}
