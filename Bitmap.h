#ifndef BITMAP_H_
#define BITMAP_H_

#include <string>
#include <cstdint>

using std::uint8_t;
using std::uint16_t;
using std::uint32_t;

class Bitmap
{
private:
  uint32_t _width{0}, _height{0};
  std::unique_ptr<uint8_t[]> _pPixels{nullptr};

public:
  Bitmap(uint32_t width, uint32_t height);
  bool write(const std::string &filename);
  void setPixel(uint32_t x, uint32_t y, uint8_t red, uint8_t green, uint8_t blue);
  uint32_t width() { return _width; }
  uint32_t height() {return _height; }
  virtual ~Bitmap() {}
};

#endif
