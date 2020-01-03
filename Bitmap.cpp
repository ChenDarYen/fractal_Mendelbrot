#include "Bitmap.h"
#include <fstream>

Bitmap::Bitmap(uint32_t w, uint32_t h) : 
            _width(w), _height(h),
            _pPixels(std::make_unique<uint8_t[]>(w * h * 3)) {}

bool Bitmap::write(const std::string &fileName)
{
  BmpFileHeader fileHeader;
  BmpInfoHeader infoHeader;

  fileHeader.size = 54u + _width*_height*3;

  infoHeader.width = _width;
  infoHeader.height = _height;

  std::ofstream file;
  file.open(fileName, std::ios::out | std::ios::binary);

  if (!file)
    return false;

  file.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
  file.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
  file.write(reinterpret_cast<char*>(_pPixels.get()), _width * _height * 3u);

  file.close();

  if(!file)
    return false;

  return true;
}

void Bitmap::setPixel(uint32_t x, uint32_t y, uint8_t red, uint8_t green, uint8_t blue)
{
  uint8_t *pPixel = _pPixels.get();
  pPixel += _width*(y*3) + x*3;

  *pPixel++ = blue;
  *pPixel++ = green;
  *pPixel = red;
}

uint32_t Bitmap::width() { return _width; }

uint32_t Bitmap::height() { return _height; }
