#ifndef FRACTAL_CREATOR_H_
#define FRACTAL_CREATOR_H_

#include <string>
#include <vector>
#include <complex>
#include <SDL.h>
#include "Zoom_List.h"
#include "Bitmap.h"
#include "Screen.h"
#include "Mandelbrot.h"
#include "RGB.h"

class Fractal_Creator
{
public:
  Fractal_Creator(int width, int height, double min_scale, int times);
  void addGrad(double percentile, const RGB &color);
  void addZoom(const Zoom &zoom);
  void addZoom(std::complex<double> translate, double scale);
  void delZoom();
  void updateScreen();
  bool writeBmp(const std::string &fileName);
  std::complex<double> coordinateTrans(int x, int y);
  std::complex<double> orign();
  void transform(const std::complex<double> &trans, double ratio);
  int width();
  int height();
  bool done();

private:
  void _reset();
  void _updateScreenInDepth(int depth);
  RGB _color(int val_itr);
  void _draw(int increase_depth);
  void _setPixel(uint32_t x, uint32_t y, uint8_t red, uint8_t green, uint8_t blue);
  void _setPixel(uint32_t x, uint32_t y, const RGB &color);
  int _width{0};
  int _height{0};
  int _curr_depth{0};
  int _deepening_times{0};
  int _curr_times{0};
  double _min_scale{0};
  std::shared_ptr<Bitmap> _pBmp{nullptr};
  std::shared_ptr<Screen> _pScreen{nullptr};
  std::unique_ptr<uint8_t[]> _pPixels{nullptr};
  std::unique_ptr<int[]> _iter_level{std::make_unique<int[]>(Mandelbrot::_maxRepeat)};
  std::unique_ptr<double[]> _iter_ratio{std::make_unique<double[]>(Mandelbrot::_maxRepeat)};
  std::unique_ptr<int[]> _histogram{std::make_unique<int[]>(Mandelbrot::_maxRepeat + 1)};
  std::unique_ptr<int[]> _fractal;
  std::unique_ptr<std::complex<double>[]> _current_z;
  Zoom_List _zooms;
  std::vector<std::pair<double, RGB>> _gradients;
};

#endif
