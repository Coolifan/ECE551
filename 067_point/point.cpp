#include <cstdlib>
#include <cstdio>
#include <cmath>
#include "point.h"

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  return sqrt( (x-p.x)*(x-p.x) + (y-p.y)*(y-p.y) );
}
