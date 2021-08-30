#include "cube.hpp"
#include <GL/gl.h>
#include <array>

namespace {
constexpr std::array<float, 72> coords = {
  // back face: ccw
  -0.5, -0.5, -0.5, 
  -0.5,  0.5, -0.5, 
   0.5,  0.5, -0.5, 
   0.5, -0.5, -0.5,
  // front face: ccw
  -0.5, -0.5, 0.5, 
   0.5, -0.5, 0.5, 
   0.5,  0.5, 0.5, 
  -0.5,  0.5, 0.5,
  // left face: ccw
  -0.5, -0.5, -0.5, 
  -0.5, -0.5,  0.5, 
  -0.5,  0.5,  0.5, 
  -0.5,  0.5, -0.5,
  // right face: ccw
  0.5, -0.5, -0.5, 
  0.5,  0.5, -0.5, 
  0.5,  0.5,  0.5, 
  0.5, -0.5,  0.5,
  // bottom face: ccw
  -0.5, -0.5, -0.5, 
   0.5, -0.5, -0.5, 
   0.5, -0.5,  0.5, 
  -0.5, -0.5,  0.5,
  // top face: ccw
   0.5, 0.5,  0.5,
   0.5, 0.5, -0.5, 
  -0.5, 0.5, -0.5, 
  -0.5, 0.5,  0.5
};

constexpr std::array<float, 72> normals = {
  // back face
  0.0, 0.0, -1.0, 
  0.0, 0.0, -1.0, 
  0.0, 0.0, -1.0, 
  0.0, 0.0, -1.0,

  // front face
  0.0, 0.0, 1.0, 
  0.0, 0.0, 1.0, 
  0.0, 0.0, 1.0, 
  0.0, 0.0, 1.0,

  // left face
  -1.0, 0.0, 0.0, 
  -1.0, 0.0, 0.0, 
  -1.0, 0.0, 0.0, 
  -1.0, 0.0, 0.0,
  
  // right face
  1.0, 0.0, 0.0, 
  1.0, 0.0, 0.0, 
  1.0, 0.0, 0.0, 
  1.0, 0.0, 0.0,

  // bottom face
  0.0, -1.0, 0.0, 
  0.0, -1.0, 0.0, 
  0.0, -1.0, 0.0, 
  0.0, -1.0, 0.0,

  // top face
  0.0, 1.0, 0.0, 
  0.0, 1.0, 0.0, 
  0.0, 1.0, 0.0, 
  0.0, 1.0, 0.0
};
}  // anonymous namespace

void Cube::draw() const
{
  glVertexPointer(3, GL_FLOAT, 0, coords.data());
  glNormalPointer(GL_FLOAT, 0, normals.data());

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  glDrawArrays(GL_QUADS, 0, 24);
}