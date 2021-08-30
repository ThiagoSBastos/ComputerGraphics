#ifndef CUBE_HPP
#define CUBE_HPP

#include "shape.hpp"

class Cube : public Shape<Cube> {
public:
  // Draws cube of size 1.0 at (0,0,0)
  void draw() const;
};

#endif