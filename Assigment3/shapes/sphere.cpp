#include "sphere.hpp"
#include <GL/gl.h>
#include <array>
#include <cmath>

namespace {
constexpr float m_pi = 3.1415926535897932384626433832795028;

auto getVertexArr = [](int i, int j, float dtheta, float dphi) {
  std::array<float, 18> v_arr = {
    cosf(i * dtheta) * sinf(j * dphi), cosf(j * dphi), sinf(i * dtheta) * sinf(j * dphi),
    cosf((i + 1) * dtheta) * sinf((j + 1) * dphi), cosf((j + 1) * dphi), sinf((i + 1) * dtheta) * sinf((j + 1) * dphi),
    cosf((i + 1) * dtheta) * sinf(j * dphi), cosf(j * dphi), sinf((i + 1) * dtheta) * sinf(j * dphi),
    cosf(i * dtheta) * sinf(j * dphi), cosf(j * dphi), sinf(i * dtheta) * sinf(j * dphi),
    cosf(i * dtheta) * sinf((j + 1) * dphi), cosf((j + 1) * dphi), sinf(i * dtheta) * sinf((j + 1) * dphi),
    cosf((i + 1) * dtheta) * sinf((j + 1) * dphi), cosf((j + 1) * dphi), sinf((i + 1) * dtheta) * sinf((j + 1) * dphi)
  };

  return v_arr;
};

auto getNormalArr = [](int i, int j, float dtheta, float dphi) {
  std::array<float, 18> n_arr = {
    (sinf(j * dphi) * cosf(i * dtheta)), (cosf(j * dphi)), (sinf(j * dphi) * sinf(i * dtheta)),
    (sinf((j + 1) * dphi) * cosf((i + 1) * dtheta)), (cosf((j + 1) * dphi)), (sinf((j + 1) * dphi) * sinf((i + 1) * dtheta)),
    (sinf(j * dphi) * cosf((i + 1) * dtheta)), (cosf(j * dphi)), (sinf(j * dphi) * sinf((i + 1) * dtheta)),
    (sinf(j * dphi) * cosf(i * dtheta)), (cosf(j * dphi)), (sinf(j * dphi) * sinf(i * dtheta)),
    (sinf((j + 1) * dphi) * cosf(i * dtheta)), (cosf((j + 1) * dphi)), (sinf((j + 1) * dphi) * sinf(i * dtheta)),
    (sinf((j + 1) * dphi) * cosf((i + 1) * dtheta)), (cosf((j + 1) * dphi)), (sinf((j + 1) * dphi) * sinf((i + 1) * dtheta))
  };

  return n_arr;
};

}

Sphere::Sphere(int nlong, int nlat) : m_nlong(nlong), m_nlat(nlat) {}


void Sphere::draw() const
{
  const float dtheta = (2.0 * m_pi) / m_nlat;
  const float dphi = m_pi / m_nlong;

  glBegin(GL_TRIANGLES);
  for (int j = 0; j < m_nlong; ++j) {
    for (int i = 0; i <= m_nlat; ++i) {
      auto v_arr = getVertexArr(i, j, dtheta, dphi);
      auto n_arr = getNormalArr(i, j, dtheta, dphi);
      
      glVertex3f(v_arr[0] , v_arr[1] , v_arr[2]);
      glVertex3f(v_arr[3] , v_arr[4] , v_arr[5]);
      glVertex3f(v_arr[6] , v_arr[7] , v_arr[8]);
      glVertex3f(v_arr[9] , v_arr[10], v_arr[11]);
      glVertex3f(v_arr[12], v_arr[13], v_arr[14]);
      glVertex3f(v_arr[15], v_arr[16], v_arr[17]);

      glNormal3f(n_arr[0], n_arr[1], n_arr[2]);
      glNormal3f(n_arr[3], n_arr[4], n_arr[5]);
      glNormal3f(n_arr[6], n_arr[7], n_arr[8]);
      glNormal3f(n_arr[9], n_arr[10], n_arr[11]);
      glNormal3f(n_arr[12], n_arr[13], n_arr[14]);
      glNormal3f(n_arr[15], n_arr[16], n_arr[17]);
    }
  }
  glEnd();
}