#include <cmath>
#include "Mandelbrot.h"

int Mandelbrot::cTest(std::complex<double> c)
{
  int repeat = 0;
  std::complex<double> z{0, 0};
  while(std::abs(z) < _escapeRadius && repeat < _maxReapet)
  {
    z = z*z + c;
    ++repeat;
  }

  return repeat;
}
