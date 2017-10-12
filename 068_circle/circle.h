#include "point.h"
class Circle {
  Point center;
  const double radius;
 public:
 Circle(Point p, double c) : center(p), radius(c) {}
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};
