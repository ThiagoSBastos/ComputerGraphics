#include "sphere.hpp"
#include <GL/gl.h>
#include <array>
#include <cmath>

namespace {
constexpr float m_pi = 3.1415926535897932384626433832795028;
}

Sphere::Sphere(int nlong, int nlat) : m_nlong(nlong), m_nlat(nlat) {}

void Sphere::draw() const
{
  const float dtheta = (2.0 * m_pi) / m_nlat;
  const float dphi = m_pi / m_nlong;

  glBegin(GL_TRIANGLES);
  for (int j = 0; j < m_nlong; ++j) {
    for (int i = 0; i <= m_nlat; ++i) {
      std::array<float, 3> v0 = {cosf(i * dtheta) * sinf(j * dphi), cosf(j * dphi),
                                 sinf(i * dtheta) * sinf(j * dphi)};

      std::array<float, 3> v1 = {cosf((i + 1) * dtheta) * sinf((j + 1) * dphi),
                                 cosf((j + 1) * dphi),
                                 sinf((i + 1) * dtheta) * sinf((j + 1) * dphi)};

      std::array<float, 3> v2 = {cosf((i + 1) * dtheta) * sinf(j * dphi), cosf(j * dphi),
                                 sinf((i + 1) * dtheta) * sinf(j * dphi)};

      std::array<float, 3> v3 = {cosf(i * dtheta) * sinf(j * dphi), cosf(j * dphi),
                                 sinf(i * dtheta) * sinf(j * dphi)};

      std::array<float, 3> v4 = {cosf(i * dtheta) * sinf((j + 1) * dphi),
                                 cosf((j + 1) * dphi),
                                 sinf(i * dtheta) * sinf((j + 1) * dphi)};

      std::array<float, 3> v5 = {cosf((i + 1) * dtheta) * sinf((j + 1) * dphi),
                                 cosf((j + 1) * dphi),
                                 sinf((i + 1) * dtheta) * sinf((j + 1) * dphi)};

      std::array<float, 3> n0 = {(sinf(j * dphi) * cosf(i * dtheta)), (cosf(j * dphi)),
                                 (sinf(j * dphi) * sinf(i * dtheta))};

      std::array<float, 3> n1 = {(sinf((j + 1) * dphi) * cosf((i + 1) * dtheta)),
                                 (cosf((j + 1) * dphi)),
                                 (sinf((j + 1) * dphi) * sinf((i + 1) * dtheta))};

      std::array<float, 3> n2 = {(sinf(j * dphi) * cosf((i + 1) * dtheta)),
                                 (cosf(j * dphi)),
                                 (sinf(j * dphi) * sinf((i + 1) * dtheta))};

      std::array<float, 3> n3 = {(sinf(j * dphi) * cosf(i * dtheta)), (cosf(j * dphi)),
                                 (sinf(j * dphi) * sinf(i * dtheta))};

      std::array<float, 3> n4 = {(sinf((j + 1) * dphi) * cosf(i * dtheta)),
                                 (cosf((j + 1) * dphi)),
                                 (sinf((j + 1) * dphi) * sinf(i * dtheta))};

      std::array<float, 3> n5 = {(sinf((j + 1) * dphi) * cosf((i + 1) * dtheta)),
                                 (cosf((j + 1) * dphi)),
                                 (sinf((j + 1) * dphi) * sinf((i + 1) * dtheta))};

      glVertex3f(v0[0], v0[1], v0[2]);
      glVertex3f(v1[0], v1[1], v1[2]);
      glVertex3f(v2[0], v2[1], v2[2]);
      glVertex3f(v3[0], v3[1], v3[2]);
      glVertex3f(v4[0], v4[1], v4[2]);
      glVertex3f(v5[0], v5[1], v5[2]);

      glNormal3f(n0[0], n0[1], n0[2]);
      glNormal3f(n1[0], n1[1], n1[2]);
      glNormal3f(n2[0], n2[1], n2[2]);
      glNormal3f(n3[0], n3[1], n3[2]);
      glNormal3f(n4[0], n4[1], n4[2]);
      glNormal3f(n5[0], n5[1], n5[2]);
    }
  }
  glEnd();
}