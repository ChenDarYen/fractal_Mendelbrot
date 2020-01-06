#include <stdexcept>
#include "Fractal_Creator.h"

// public

Fractal_Creator::Fractal_Creator(int width, int height, double min_scale, int times) :
    _width(width), _height(height), _min_scale(min_scale), _deepening_times(times),
    _pBmp(std::make_shared<Bitmap>(width, height)),
    _pScreen(std::make_shared<Screen>(width, height)),
    _pPixels(std::make_unique<uint8_t[]>(width * height * 3)),
    _fractal(std::make_unique<int[]>(width * height)),
    _current_z(std::make_unique<std::complex<double>[]>(width * height))
{
  _histogram[Mandelbrot::_maxRepeat] = _width * _height;
}

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

void Fractal_Creator::updateScreen()
{
  if(_curr_times != _deepening_times)
  {
    _updateScreenInDepth(Mandelbrot::_maxRepeat * (_curr_times + 1.0) / _deepening_times);
    ++_curr_times;
  }
}

bool Fractal_Creator::writeBmp(const std::string &fileName)
{
  return _pBmp->write(fileName, reinterpret_cast<char*>(_pPixels.get()));
}

std::complex<double> Fractal_Creator::coordinateTrans(int x, int y)
{
  const Zoom &zoom = _zooms.top();
  double real_part = (x - _width / 2.0) / zoom.scale;
  double image_part = -(y - _height / 2.0) / zoom.scale;

  return std::complex<double>{real_part, image_part} + zoom.translate;
}

std::complex<double> Fractal_Creator::orign()
{
  return _zooms.top().translate;
}

void Fractal_Creator::transform(const std::complex<double> &trans, double ratio)
{
  std::complex<double> o = _zooms.top().translate + trans;
  double scale = _zooms.top().scale * ratio;
  scale = std::max(scale, _min_scale);
  addZoom(o, scale);
  _reset();
}

int Fractal_Creator::width() { return _width; }

int Fractal_Creator::height() { return _height; }

// private

void Fractal_Creator::_reset()
{
  _histogram[Mandelbrot::_maxRepeat] = _width * _height;
  for(int i = 0; i < Mandelbrot::_maxRepeat; ++i)
    _histogram[i] = 0;

  for(int i = 0; i < _width * _height; ++i)
  {
    _fractal[i] = 0;
    _current_z[i] = {0, 0};
    _pPixels[i * 3] = _pPixels[i * 3 + 1] = _pPixels[i * 3 + 2] = 0;
  }

  _curr_depth = 0;
  _curr_times = 0;
}

void Fractal_Creator::_updateScreenInDepth(int depth)
{
  _draw(depth - _curr_depth);
  _curr_depth = depth;
  _pScreen->update(reinterpret_cast<char *>(_pPixels.get()));
}

RGB Fractal_Creator::_color(int val_itr)
{
  int level = _iter_level[val_itr];
  double ratio = _iter_ratio[val_itr];
  auto color_base = _gradients[level].second;
  auto color_mixed = _gradients[level + 1].second;

  return color_base * ratio + color_mixed * (1 - ratio);
}

void Fractal_Creator::_draw(int increase_depth)
{
  for(int x = 0; x < _width; ++x)
  {
    for(int y = 0; y < _height; ++y)
    {
      const int IDX = _width*y + x;

      if(_fractal[IDX] >= _curr_depth)
      {
        auto c = coordinateTrans(x, y);

        int increase_iter{0};
        Mandelbrot::cTest(_current_z[IDX], c, increase_depth, &increase_iter, &_current_z[IDX]);
        _fractal[IDX] += increase_iter;

        if(_fractal[IDX] < increase_depth + _curr_depth)
        {
          --_histogram[Mandelbrot::_maxRepeat];
          ++_histogram[_fractal[IDX]];
        }
      }
    }
  }

  int total = _width*_height - _histogram[Mandelbrot::_maxRepeat];
  int count = 0, level = 0;
  for(int i = 0; i < increase_depth + _curr_depth; ++i)
  {
    double percentile = static_cast<double>(count) / total;
    while(_gradients[level+1].first < percentile)
      ++level;

    _iter_level[i] = level;
    _iter_ratio[i] = (_gradients[level+1].first - percentile) / (_gradients[level+1].first - _gradients[level].first);
    
    count += _histogram[i];
  }

  for(int x = 0; x < _width; ++x)
  {
    for(int y = 0; y < _height; ++y)
    {
      int v_iter = _fractal[_width*y + x];
      if(v_iter < increase_depth + _curr_depth)
        _setPixel(x, y, _color(v_iter));
    }
  }
}

void Fractal_Creator::_setPixel(uint32_t x, uint32_t y, uint8_t red, uint8_t green, uint8_t blue)
{
  uint8_t *pPixel = _pPixels.get();
  pPixel += _width * (y * 3) + x * 3;

  pPixel[0] = red;
  pPixel[1] = green;
  pPixel[2] = blue;
}

void Fractal_Creator::_setPixel(uint32_t x, uint32_t y, const RGB &color)
{
  _setPixel(x, y, color.r, color.g, color.b);
}
