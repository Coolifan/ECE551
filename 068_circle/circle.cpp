#include "circle.h"
#include <cstdio>
#include <cstdlib>
#include <cmath>

void Circle::move(double dx, double dy) {
  center.move(dx,dy);
}
  
double Circle::intersectionArea(const Circle & otherCircle) {
  double r1 = radius;
  double r2 = otherCircle.radius;
  if (r2 < r1) {
    r1 = otherCircle.radius;
    r2 = radius;
  }
  double d = center.distanceFrom(otherCircle.center);

  if (r1 == 0 || r2 == 0) {
    return 0.0;
  }
  else if (d <= r2-r1) {
    return 3.1415926535*r1*r1;
  }
  else if (d >= r2+r1) {
    return 0.0;
  }
  else {
    double add1 = r1*r1*acos( (d*d + r1*r1 - r2*r2) / (2*d*r1)); 
    double add2 = r2*r2*acos( (d*d + r2*r2 - r1*r1) / (2*d*r2));
    double add3 = 0.5 * sqrt( (-d+r1+r2)*(d+r1-r2)*(d-r1+r2)*(d+r1+r2) ); 
    return add1+add2-add3;
  }
  
}

