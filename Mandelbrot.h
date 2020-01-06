#ifndef MANDEL_H_
#define MANDEL_H_

#include <string>
#include <complex>

class Mandelbrot
{
public:
  static void cTest(std::complex<double> init_val, std::complex<double> c, int depth, int *pV_iter, std::complex<double> *pZ);
  static const int _escapeRadius = 2;
  static const int _maxRepeat = 1000;
};

#endif
