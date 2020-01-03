#ifndef MANDEL_H_
#define MANDEL_H_

#include <string>
#include <complex>

class Bitmap;
class Zoom;
class Mandelbrot
{
public:
  Mandelbrot(Bitmap &bmp, const Zoom &zoom);
  void draw();
  bool write(const std::string &fileName);

private:
  static int cTest(std::complex<double> c);
  static const int _escapeRadius = 2;
  static const int _maxReapet = 1000;
  Bitmap *_pBmp;
  int _scale;
  std::complex<double> _trans;
};

#endif
