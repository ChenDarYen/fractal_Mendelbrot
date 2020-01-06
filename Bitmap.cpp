#include "Bitmap.h"
#include <fstream>

Bitmap::Bitmap(uint32_t w, uint32_t h) : 
            _width(w), _height(h),
            _pPixels(std::make_unique<uint8_t[]>(w * h * 3)) {}

bool Bitmap::write(const std::string &fileName, const char *pPixels)
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
  file.write(pPixels, _width * _height * 3u);

  file.close();

  if(!file)
    return false;

  return true;
}

uint32_t Bitmap::width() { return _width; }

uint32_t Bitmap::height() { return _height; }
