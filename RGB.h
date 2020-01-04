#ifndef RGB_H_
#define RGB_H_

struct RGB
{
  RGB(short r, short g, short b);
  RGB operator*(double ratio);
  short r;
  short g;
  short b;
};

RGB operator+(const RGB &rhs, const RGB &lhs);

#endif
