#ifndef ZOOM_LIST_H_
#define ZOOM_LIST_H_

#include <vector>
#include <complex>


class Zoom;
class Zoom_List
{
public:
  void push(const Zoom &zoom);
  void push(std::complex<double> translate, double scale);
  void pop();
  Zoom &top();

private:
  std::vector<Zoom> _zooms;
};

#endif
