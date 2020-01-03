#ifndef FRACTAL_CREATOR_H_
#define FRACTAL_CREATOR_H_

#include <string>
#include "Zoom_List.h"
#include "Bitmap.h"
#include "Mandelbrot.h"

class Fractal_Creator
{
public:
  Fractal_Creator(Bitmap &bmp);
  void addZoom(const Zoom &zoom);
  void addZoom(std::complex<double> translate, double scale);
  void delZoom();
  void draw();
  bool writeBmp(const std::string &fileName);

private:
  Bitmap *_pBmp;
  Zoom_List _zooms;
  Mandelbrot _fractal;
};

#endif
