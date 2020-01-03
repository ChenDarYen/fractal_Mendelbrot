#include <iostream>
#include "Bitmap.cpp"
#include "Mandelbrot.cpp"
#include "Zoom_List.cpp"

using std::cout;
using std::endl;

int main()
{
  const unsigned WIDTH = 880, HEIGHT = 500;

  Bitmap bitmap(WIDTH, HEIGHT);

  double scale = std::min(WIDTH, HEIGHT) / 2.3;
  Zoom_List zooms;
  zooms.push({-0.5, 0}, scale);

  Mandelbrot mandelbrot(bitmap, zooms.top());
  mandelbrot.draw();
  
  if(mandelbrot.write("test.bmp"))
    cout << "finished." << endl;

  return 0;
}
