#include <cmath>
#include <complex>
#include "Bitmap.h"
#include "Mandelbrot.h"
#include "Zoom.h"

Mandelbrot::Mandelbrot(Bitmap &bmp, const Zoom &zoom) :
                    _pBmp(&bmp), _scale(zoom.scale), _trans(zoom.translate) {}

void Mandelbrot::draw()
{
  const int width = _pBmp->width();
  const int height = _pBmp->height();
  std::unique_ptr<int[]> histogram = std::make_unique<int[]>(_maxReapet + 1);
  std::unique_ptr<int[]> fractal = std::make_unique<int[]>(width*height);

  for(int x = 0; x < _pBmp->width(); ++x)
  {
    for(int y = 0; y < _pBmp->height(); ++y)
    {

      double real_part = (x - width/2.0) / _scale;
      double image_part = (y - height/2.0) / _scale;
      std::complex<double> c{real_part , image_part};
      c += _trans;

      int v_iter = cTest(c);
      ++histogram[v_iter];
      fractal[width*y + x] = v_iter;
    }
  }

  std::unique_ptr<int[]> accumulate = std::make_unique<int[]>(_maxReapet);
  accumulate[0] = histogram[0];
  for(int i = 1; i < _maxReapet; ++i)
    accumulate[i] = accumulate[i-1] + histogram[i];


  for(int x = 0; x < width; ++x)
  {
    for(int y = 0; y < height; ++y)
    {
      int v_iter = fractal[width*y + x];
      if(v_iter != _maxReapet)
      {
        double hue = static_cast<double>(accumulate[v_iter]) / (width * height);
        uint8_t red = pow(256 * v_iter / _maxReapet, 3);
        uint8_t green = pow(255, hue);
        uint8_t blue = 30 + 256 * v_iter / _maxReapet;
        _pBmp->setPixel(x, y, red, green, blue);
      }
    }
  }
}

bool Mandelbrot::write(const std::string &fileName)
{
  return _pBmp->write(fileName);
}

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
