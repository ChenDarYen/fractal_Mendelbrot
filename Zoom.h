#ifndef ZOOM_H_
#define ZOOM_H_

#include <complex>

struct Zoom
{
  std::complex<double> translate{0, 0};
  double scale;
};

#endif
