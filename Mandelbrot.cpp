#include <cmath>
#include "Mandelbrot.h"

void Mandelbrot::cTest(std::complex<double> init_val, std::complex<double> c, int depth, int *pV_iter, std::complex<double> *pZ)
{
  int repeat = 0;
  std::complex<double> z{init_val};
  while(std::abs(z) < _escapeRadius && repeat < depth)
  {
    z = z*z + c;
    ++repeat;
  }

  *pV_iter = repeat;
  *pZ = z;
}
