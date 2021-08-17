#include <GL/freeglut.h>
#include <GL/gl.h>
#include <array>
#include <cmath>

namespace cfg {
static constexpr std::array<int, 2> window_sz = {600, 400};
static constexpr std::array<float, 3> center = {0.0f, 0.0f, 0.0f};
static constexpr std::array<float, 3> up_dir = {0.0f, 1.0f, 0.0f};
static constexpr std::array<float, 4> bg_color = {1.0f, 1.0f, 1.0f, 1.0f};
static constexpr float cam_angle = 45.0;
static constexpr float cam_near = 1.0;
static constexpr float cam_far = 10.0;
}  // namespace cfg

std::array<float, 4> eye = {2.0f, 3.0f, 4.0f, 1.0f};

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
  gluLookAt(eye[0], eye[1], eye[2], cfg::center[0], cfg::center[1], cfg::center[2],
            cfg::up_dir[0], cfg::up_dir[1], cfg::up_dir[2]);
}

// Draws cube of size 1.0 at (0,0,0)
static void drawCube()
{
  glBegin(GL_QUADS);

  // left face:
  glNormal3f(-1.0f, 0.0f, 0.0f);
  glNormal3f(-1.0f, 0.0f, 0.0f);
  glNormal3f(-1.0f, 0.0f, 0.0f);
  glNormal3f(-1.0f, 0.0f, 0.0f);

  glVertex3f(-0.5f, -0.5f, -0.5f);
  glVertex3f(-0.5f, -0.5f, 0.5f);
  glVertex3f(-0.5f, 0.5f, 0.5f);
  glVertex3f(-0.5f, 0.5f, -0.5f);

  // right face: counter clockwise
  glNormal3f(1.0f, 0.0f, 0.0f);
  glNormal3f(1.0f, 0.0f, 0.0f);
  glNormal3f(1.0f, 0.0f, 0.0f);
  glNormal3f(1.0f, 0.0f, 0.0f);

  glVertex3f(0.5f, -0.5f, -0.5f);
  glVertex3f(0.5f, 0.5f, -0.5f);
  glVertex3f(0.5f, 0.5f, 0.5f);
  glVertex3f(0.5f, -0.5f, 0.5f);

  // top face:
  glNormal3f(0.0f, 1.0f, 0.0f);
  glNormal3f(0.0f, 1.0f, 0.0f);
  glNormal3f(0.0f, 1.0f, 0.0f);
  glNormal3f(0.0f, 1.0f, 0.0f);

  glVertex3f(0.5f, 0.5f, 0.5f);
  glVertex3f(0.5f, 0.5f, -0.5f);
  glVertex3f(-0.5f, 0.5f, -0.5f);
  glVertex3f(-0.5f, 0.5f, 0.5f);

  // bottom face:
  glNormal3f(0.0f, -1.0f, 0.0f);
  glNormal3f(0.0f, -1.0f, 0.0f);
  glNormal3f(0.0f, -1.0f, 0.0f);
  glNormal3f(0.0f, -1.0f, 0.0f);

  glVertex3f(-0.5f, -0.5f, -0.5f);
  glVertex3f(0.5f, -0.5f, -0.5f);
  glVertex3f(0.5f, -0.5f, 0.5f);
  glVertex3f(-0.5f, -0.5f, 0.5f);

  // front face:
  glNormal3f(0.0f, 0.0f, 1.0f);
  glNormal3f(0.0f, 0.0f, 1.0f);
  glNormal3f(0.0f, 0.0f, 1.0f);
  glNormal3f(0.0f, 0.0f, 1.0f);

  glVertex3f(-0.5f, -0.5f, 0.5f);
  glVertex3f(0.5f, -0.5f, 0.5f);
  glVertex3f(0.5f, 0.5f, 0.5f);
  glVertex3f(-0.5f, 0.5f, 0.5f);

  // back face:
  glNormal3f(0.0f, 0.0f, -1.0f);
  glNormal3f(0.0f, 0.0f, -1.0f);
  glNormal3f(0.0f, 0.0f, -1.0f);
  glNormal3f(0.0f, 0.0f, -1.0f);

  glVertex3f(-0.5f, -0.5f, -0.5f);
  glVertex3f(-0.5f, 0.5f, -0.5f);
  glVertex3f(0.5f, 0.5f, -0.5f);
  glVertex3f(0.5f, -0.5f, -0.5f);

  glEnd();
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

      std::array<float, 3> v4 = {cosf(i * dtheta) * sinf((j + 1) * dphi), cosf((j + 1) * dphi),
                       sinf(i * dtheta) * sinf((j + 1) * dphi)};

      std::array<float, 3> v5 = {cosf((i + 1) * dtheta) * sinf((j + 1) * dphi),
                       cosf((j + 1) * dphi),
                       sinf((i + 1) * dtheta) * sinf((j + 1) * dphi)};

      std::array<float, 3> n0 = {(sinf(j * dphi) * cosf(i * dtheta)), (cosf(j * dphi)),
                       (sinf(j * dphi) * sinf(i * dtheta))};

      std::array<float, 3> n1 = {(sinf((j + 1) * dphi) * cosf((i + 1) * dtheta)),
                       (cosf((j + 1) * dphi)),
                       (sinf((j + 1) * dphi) * sinf((i + 1) * dtheta))};

      std::array<float, 3> n2 = {(sinf(j * dphi) * cosf((i + 1) * dtheta)), (cosf(j * dphi)),
                       (sinf(j * dphi) * sinf((i + 1) * dtheta))};

      std::array<float, 3> n3 = {(sinf(j * dphi) * cosf(i * dtheta)), (cosf(j * dphi)),
                       (sinf(j * dphi) * sinf(i * dtheta))};

      std::array<float, 3> n4 = {(sinf((j + 1) * dphi) * cosf(i * dtheta)), (cosf((j + 1) * dphi)),
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
  std::array<float, 4> amb = {0.1f, 0.1f, 0.1f, 1.0f};
  std::array<float, 4> dif = {0.7f, 0.7f, 0.7f, 1.0f};
  std::array<float, 4> spe = {1.0f, 1.0f, 1.0f, 1.0f};

  glLightfv(GL_LIGHT0, GL_POSITION, eye.data());
  glLightfv(GL_LIGHT0, GL_AMBIENT, amb.data());
  glLightfv(GL_LIGHT0, GL_DIFFUSE, dif.data());
  glLightfv(GL_LIGHT0, GL_SPECULAR, spe.data());

  std::array<float, 4> red = {1.0f, 0.0f, 0.0f, 1.0f};
  std::array<float, 4> white = {1.0f, 1.0f, 1.0f, 1.0f};

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red.data());
  glMaterialfv(GL_FRONT, GL_SPECULAR, white.data());
  glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);

  drawSphere(64, 64);
}

static void myDisplayCB()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  setCamera();
  drawScene();
  glutSwapBuffers();  // update screen
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
}

int main(int argc, char** argv)
{
  // open GLUT
  glutInit(&argc, argv);

  // configure and create window
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(cfg::window_sz[0], cfg::window_sz[1]);
  glutCreateWindow("MyScene");

  glutDisplayFunc(myDisplayCB);
  glutKeyboardFunc(myKeyboardCB);

  initialize();
  glutMainLoop();

  return 0;
}
