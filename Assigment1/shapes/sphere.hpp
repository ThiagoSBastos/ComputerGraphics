#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"

class Sphere : public Shape<Sphere> {
public:
  // @param n_long: resolution on the longitudinal direction
  // @param n_lat: resolution on the latitudinal direction
  explicit Sphere(int nlong, int nlat);

  // Draws a sphere with r = 1.0 at (0,0,0)
  void draw() const;
private:
  int m_nlong;
  int m_nlat;
};

#endif