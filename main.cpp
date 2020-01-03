#include <iostream>
#include "Bitmap.cpp"
#include "Mandelbrot.cpp"

using std::cout;
using std::endl;

int main()
{
  const unsigned WIDTH = 880, HEIGHT = 500;

  Bitmap bitmap(WIDTH, HEIGHT);

  double scale = std::min(WIDTH, HEIGHT) / 2.3;
  Mandelbrot mandelbrot(bitmap, scale, -0.5, 0);
  mandelbrot.draw();
  
  if(mandelbrot.write("test.bmp"))
    cout << "finished." << endl;

  return 0;
}
