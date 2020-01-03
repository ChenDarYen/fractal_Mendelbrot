#include <iostream>
#include "Bitmap.cpp"
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
  fractal.addZoom({-0.5, 0.5}, scale*6);
  
  fractal.draw();
  if (fractal.writeBmp("test.bmp"))
    cout << "finished." << endl;

  return 0;
}
