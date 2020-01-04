#include "RGB.h"

RGB::RGB(short r, short g, short b) : r(r), g(g), b(b) {}

RGB RGB::operator*(double ratio) { return RGB(r*ratio, g*ratio, b*ratio); }

RGB operator+(const RGB &lhs, const RGB &rhs)
{
  return RGB(lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b);
}
