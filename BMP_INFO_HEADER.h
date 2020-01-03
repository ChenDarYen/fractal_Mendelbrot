#ifndef BMP_INFO_HEADER_H_
#define BMP_INFO_HEADER_H_

#include <cstdint>

#pragma pack(2)

using std::uint16_t;
using std::uint32_t;

struct BmpInfoHeader
{
  uint32_t size{40};
  uint32_t width;
  uint32_t height;
  uint16_t plane{1};
  uint16_t bitPerPixel{24};
  uint32_t compression{0};
  uint32_t dataSize{0};
  uint32_t xResolution{2400};
  uint32_t yResolution{2400};
  uint32_t color{0};
  uint32_t importantColor{0};
};

#endif
