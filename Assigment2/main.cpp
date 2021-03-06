#include <GL/freeglut.h>
#include <GL/gl.h>
#include <array>
#include <cmath>
#include <cstdio>

namespace cfg {
static constexpr std::array<int, 2> window_sz = {600, 400};
static constexpr std::array<float, 3> center = {0.0f, 0.0f, 0.0f};
static constexpr std::array<float, 3> up_dir = {0.0f, 1.0f, 0.0f};
static constexpr std::array<float, 4> bg_color = {1.0f, 1.0f, 1.0f, 1.0f};
static constexpr float cam_angle = 45.0;
static constexpr float cam_near = 1.0;
static constexpr float cam_far = 20.0;

static constexpr float earth_to_sun_radius = 4.0;
static constexpr float moon_to_earth_radius = 2.0;

}  // namespace cfg

static std::array<float, 4> eye = {4.0f, 6.0f, 8.0f, 1.0f};
static float angle = 0.0f;
static float angle_moon = 0.0f;

static void setCamera()
{
  std::array<int, 4> vp;  // viewport dimension: {x0, y0, w, h}

  glGetIntegerv(GL_VIEWPORT, vp.data());
  float ratio = static_cast<float>(vp[2]) / vp[3];

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(cfg::cam_angle, ratio, cfg::cam_near, cfg::cam_far);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //gluLookAt(eye[0], eye[1], eye[2], cfg::center[0], cfg::center[1], cfg::center[2],
  //          cfg::up_dir[0], cfg::up_dir[1], cfg::up_dir[2]);
}

// Draws a sphere with r = 1.0 at (0,0,0)
// @param n_lat: resolution on the latitudinal direction
// @param n_long: resolution on the longitudinal direction
static void drawSphere(int n_lat, int n_long)
{
  constexpr float m_pi = 3.1415926535897932384626433832795028;
  const float dtheta = (2.0 * m_pi) / n_lat;
  const float dphi = m_pi / n_long;

  glBegin(GL_TRIANGLES);
  for (int j = 0; j < n_long; ++j) {
    for (int i = 0; i <= n_lat; ++i) {
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

static void drawScene()
{
  // Light specs
  constexpr std::array<float, 4> amb = {0.1f, 0.1f, 0.1f, 1.0f};
  constexpr std::array<float, 4> dif = {0.7f, 0.7f, 0.7f, 1.0f};
  constexpr std::array<float, 4> spe = {1.0f, 1.0f, 1.0f, 1.0f};

  glLightfv(GL_LIGHT0, GL_POSITION, eye.data());
  glLightfv(GL_LIGHT0, GL_AMBIENT, amb.data());
  glLightfv(GL_LIGHT0, GL_DIFFUSE, dif.data());
  glLightfv(GL_LIGHT0, GL_SPECULAR, spe.data());

  // Color specs
  constexpr std::array<float, 4> yellow = {1.0f, 0.667, 0.11372549, 1.0f};
  constexpr std::array<float, 4> gray = {0.8f, 0.8f, 0.8f, 1.0f};
  constexpr std::array<float, 4> blue = {0.0f, 0.0f, 1.0f, 1.0f};

  // Sun
  glPushMatrix();
  glLoadIdentity();
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow.data());
  drawSphere(128, 128);

  // Earth
  glRotatef(angle, 0.0f, 1.0f, 0.0f);
  glTranslatef(cfg::earth_to_sun_radius, 0.0f, 0.0f);
  glScalef(0.7f, 0.7f, 0.7f);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue.data());
  glPopMatrix();


  glPushMatrix();
  glLoadIdentity();
  std::array<float, 16> e;
  glGetFloatv(GL_MODELVIEW_MATRIX, e.data());

  // multiply 'e' w/ [0,0,0,1] --> [e12, e13, e14]
  float ex = e[12];
  float ey = e[13];
  float ez = e[14];

  drawSphere(128, 128);

  // Moon
  glRotatef(angle_moon, 0.0f, 1.0f, 0.0f);
  glTranslatef(cfg::moon_to_earth_radius, 0.0f, 0.0f);
  glScalef(0.4f, 0.4f, 0.4f);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray.data());  
  
  std::array<float, 16> m;
  glGetFloatv(GL_MODELVIEW_MATRIX, m.data());

  // multiply 'm' w/ [0,0,0,1] --> [m12, m13, m14]
  float mx = m[12];
  float my = m[13];
  float mz = m[14];

  drawSphere(128, 128);
  glPopMatrix();

  gluLookAt(ex, ey, ez, mx, my, mz, 0.0f, -1.0f, 0.0f);
}

static void myIdleCB()
{
  angle += 1.0f;
  if (angle > 360.0f) {
    angle = 1.0f;
  }

  angle_moon += 1.5f;
  if (angle_moon > 360.0f) {
    angle_moon = 1.5;
  }

  glutPostRedisplay();
}

static void myDisplayCB()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  setCamera();
  drawScene();
  glutSwapBuffers();  // update screen

  auto error = glGetError();
  if (error) printf("Error %d \n", error);
}

static void myKeyboardCB(uint8_t key, int x, int y)
{
  switch (key) {
    case 'x':
      eye[0] *= -1;
      break;
    case 'y':
      eye[1] *= -1;
      break;
    case 'z':
      eye[2] *= -1;
      break;
    case 'q':
      exit(0);
      break;
  }
  glutPostRedisplay();
}

static void initialize()
{
  // set background to white
  glClearColor(cfg::bg_color[0], cfg::bg_color[1], cfg::bg_color[2], cfg::bg_color[3]);

  // enable depth test
  glEnable(GL_DEPTH_TEST);

  // enable lighting computation
  glEnable(GL_LIGHTING);

  // enable light source number 0
  glEnable(GL_LIGHT0);

  // renormalize the vectors after transformations
  glEnable(GL_NORMALIZE);
}

int main(int argc, char** argv)
{
  // open GLUT
  glutInit(&argc, argv);

  // configure and create window
  glutInitWindowSize(cfg::window_sz[0], cfg::window_sz[1]);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutCreateWindow("MyScene");

  glutIdleFunc(myIdleCB);
  glutDisplayFunc(myDisplayCB);
  glutKeyboardFunc(myKeyboardCB);

  initialize();
  glutMainLoop();

  return 0;
}
