#ifndef MANDEL_H_
#define MANDEL_H_

#include <string>
#include <complex>

class Mandelbrot
{
public:
  static int cTest(std::complex<double> c);
  static const int _escapeRadius = 2;
  static const int _maxReapet = 1000;
};

#endif
