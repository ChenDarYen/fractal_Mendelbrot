#include "Fractal_Creator.h"

Fractal_Creator::Fractal_Creator(Bitmap &bmp) : _pBmp(&bmp) {}

void Fractal_Creator::addGrad(double percentile, const RGB &color)
{
  _gradients.push_back({percentile , color});
}

void Fractal_Creator::addZoom(const Zoom &zoom) { _zooms.push(zoom); }

void Fractal_Creator::addZoom(std::complex<double> translate, double scale)
{
  _zooms.push(translate, scale);
}

void Fractal_Creator::delZoom() { _zooms.pop(); }

bool Fractal_Creator::writeBmp(const std::string &fileName)
{
  _draw();
  return _pBmp->write(fileName);
}

RGB Fractal_Creator::_color(int val_itr)
{
  int level = _iter_level[val_itr];
  double ratio = _iter_ratio[val_itr];
  auto color_base = _gradients[level].second;
  auto color_mixed = _gradients[level + 1].second;

  return color_base * ratio + color_mixed * (1 - ratio);
}

void Fractal_Creator::_draw()
{
  const int width = _pBmp->width();
  const int height = _pBmp->height();
  const Zoom &zoom = _zooms.top();
  std::unique_ptr<int[]> histogram = std::make_unique<int[]>(Mandelbrot::_maxReapet + 1);
  std::unique_ptr<int[]> fractal = std::make_unique<int[]>(width*height);

  for(int x = 0; x < _pBmp->width(); ++x)
  {
    for(int y = 0; y < _pBmp->height(); ++y)
    {

      double real_part = (x - width/2.0) / zoom.scale;
      double image_part = (y - height/2.0) / zoom.scale;
      std::complex<double> c{real_part , image_part};
      c += zoom.translate;

      int v_iter = Mandelbrot::cTest(c);
      ++histogram[v_iter];
      fractal[width*y + x] = v_iter;
    }
  }

  int total = width*height - histogram[Mandelbrot::_maxReapet];
  int count = 0, level = 0;
  for(int i = 0; i < Mandelbrot::_maxReapet; ++i)
  {
    double percentile = static_cast<double>(count) / total;
    while(_gradients[level+1].first < percentile)
      ++level;

    _iter_level[i] = level;
    _iter_ratio[i] = (_gradients[level+1].first - percentile) / (_gradients[level+1].first - _gradients[level].first);
    
    count += histogram[i];
  }

  for(int x = 0; x < width; ++x)
  {
    for(int y = 0; y < height; ++y)
    {
      int v_iter = fractal[width*y + x];
      if(v_iter != Mandelbrot::_maxReapet)
        _pBmp->setPixel(x, y, _color(v_iter));
    }
  }
}
