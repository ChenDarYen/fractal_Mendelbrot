#ifndef FRACTAL_CREATOR_H_
#define FRACTAL_CREATOR_H_

#include <string>
#include <vector>
#include "Zoom_List.h"
#include "Bitmap.h"
#include "Mandelbrot.h"
#include "RGB.h"

class Fractal_Creator
{
public:
  Fractal_Creator(Bitmap &bmp);
  void addGrad(double percentile, const RGB &color);
  void addZoom(const Zoom &zoom);
  void addZoom(std::complex<double> translate, double scale);
  void delZoom();
  bool writeBmp(const std::string &fileName);

private:
  RGB _color(int val_itr);
  void _draw();
  Bitmap *_pBmp;
  Zoom_List _zooms;
  Mandelbrot _fractal;
  std::vector<std::pair<double, RGB>> _gradients;
  std::unique_ptr<int[]> _iter_level{std::make_unique<int[]>(Mandelbrot::_maxReapet)};
  std::unique_ptr<double[]> _iter_ratio{std::make_unique<double[]>(Mandelbrot::_maxReapet)};
};

#endif
