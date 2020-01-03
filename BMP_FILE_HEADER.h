#ifndef BMP_FILE_HEADER_H_
#define BMP_FILE_HEADER_H_

#include <cstdint>

#pragma pack(2)  // since all member contain 2k bytes.

using std::uint32_t;
using std::uint16_t;

struct BmpFileHeader
{
  unsigned char header[2]{'B', 'M'};
  uint32_t size;
  uint16_t reserved1{0};
  uint16_t reserved2{0};
  uint32_t dataOffset{54};
};

#endif
