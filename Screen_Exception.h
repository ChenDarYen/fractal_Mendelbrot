#ifndef SCREEN_EXCEPTION_H_
#define SCREEN_EXCEPTION_H_

#include <stdexcept>

struct Screen_Exception : std::runtime_error
{
  using std::runtime_error::runtime_error;
};

#endif
