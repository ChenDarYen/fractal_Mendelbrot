#include "Fractal_Creator.h"

Fractal_Creator::Fractal_Creator(Bitmap &bmp) : _pBmp(&bmp) {}

void Fractal_Creator::addZoom(const Zoom &zoom) { _zooms.push(zoom); }

void Fractal_Creator::addZoom(std::complex<double> translate, double scale)
{
  _zooms.push(translate, scale);
}

void Fractal_Creator::delZoom() { _zooms.pop(); }

bool Fractal_Creator::writeBmp(const std::string &fileName)
{
  draw();
  return _pBmp->write(fileName);
}

void Fractal_Creator::draw()
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

  std::unique_ptr<int[]> accumulate = std::make_unique<int[]>(Mandelbrot::_maxReapet);
  accumulate[0] = histogram[0];
  for(int i = 1; i < Mandelbrot::_maxReapet; ++i)
    accumulate[i] = accumulate[i-1] + histogram[i];


  for(int x = 0; x < width; ++x)
  {
    for(int y = 0; y < height; ++y)
    {
      int v_iter = fractal[width*y + x];
      if(v_iter != Mandelbrot::_maxReapet)
      {
        double hue = static_cast<double>(accumulate[v_iter]) / (width * height);
        uint8_t red = pow(256 * v_iter / Mandelbrot::_maxReapet, 3);
        uint8_t green = pow(255, hue);
        uint8_t blue = 30 + 256 * v_iter / Mandelbrot::_maxReapet;
        _pBmp->setPixel(x, y, red, green, blue);
      }
    }
  }
}
