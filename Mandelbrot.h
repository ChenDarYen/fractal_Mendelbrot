#ifndef MANDEL_H_
#define MANDEL_H_

#include <string>
#include <complex>

class Bitmap;
class Mandelbrot
{
public:
  Mandelbrot(Bitmap &bmp, double s, double x_trans = 0, double y_trans = 0);
  void draw();
  bool write(const std::string &fileName);

private:
  static int cTest(std::complex<double> c);
  static const int _escapeRadius = 2;
  static const int _maxReapet = 1000;
  Bitmap *_pBmp;
  int _scale;
  double _x_trans, _y_trans;
};

#endif
