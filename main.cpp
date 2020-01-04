#include <iostream>
#include "Bitmap.cpp"
#include "RGB.cpp"
#include "Zoom_List.cpp"
#include "Mandelbrot.cpp"
#include "Fractal_Creator.cpp"

using std::cout;
using std::endl;

int main()
{
  const unsigned WIDTH = 880, HEIGHT = 500;
  double scale = std::min(WIDTH, HEIGHT) / 2.3;

  Bitmap bitmap(WIDTH, HEIGHT);
  Fractal_Creator fractal(bitmap);

  fractal.addZoom({-0.5, 0}, scale);
  fractal.addZoom({-0.52, 0.62}, scale*32);
  fractal.addGrad(0, RGB(0, 0, 40));
  fractal.addGrad(0.4, RGB(0, 0, 50));
  fractal.addGrad(0.7, RGB(10, 10, 60));
  fractal.addGrad(0.9, RGB(80, 90, 60));
  fractal.addGrad(0.95, RGB(140, 140, 70));
  fractal.addGrad(0.97, RGB(180, 70, 70));
  fractal.addGrad(0.98, RGB(200, 0, 0));
  fractal.addGrad(0.999, RGB(180, 100, 100));
  fractal.addGrad(1, RGB(200, 0, 0));
  
  if (fractal.writeBmp("test.bmp"))
    cout << "finished." << endl;

  return 0;
}
