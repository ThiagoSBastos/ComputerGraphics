#include <GL/freeglut.h>
#include <GL/gl.h>
#include <array>
#include <cstdio>
#include "shapes/sphere.hpp"
#include "shapes/cube.hpp"

namespace cfg {
static constexpr std::array<int, 2> window_sz = {600, 400};
static constexpr auto title = "MyScene";

static constexpr std::array<float, 3> center = {0.0f, 0.0f, 0.0f};
static constexpr std::array<float, 3> up_dir = {0.0f, 1.0f, 0.0f};
static constexpr std::array<float, 4> bg_color = {1.0f, 1.0f, 1.0f, 1.0f};
static constexpr float cam_angle = 45.0;
static constexpr float cam_near = 1.0;
static constexpr float cam_far = 20.0;
}  // namespace cfg

std::array<float, 4> eye = {4.0f, 6.0f, 8.0f, 1.0f};

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

static void drawScene()
{
  constexpr std::array<float, 4> amb = {0.1f, 0.1f, 0.1f, 1.0f};
  constexpr std::array<float, 4> dif = {0.7f, 0.7f, 0.7f, 1.0f};
  constexpr std::array<float, 4> spe = {1.0f, 1.0f, 1.0f, 1.0f};

  glLightfv(GL_LIGHT0, GL_POSITION, eye.data());
  glLightfv(GL_LIGHT0, GL_AMBIENT, amb.data());
  glLightfv(GL_LIGHT0, GL_DIFFUSE, dif.data());
  glLightfv(GL_LIGHT0, GL_SPECULAR, spe.data());

  constexpr std::array<float, 4> red = {1.0f, 0.0f, 0.0f, 1.0f};
  constexpr std::array<float, 4> white = {1.0f, 1.0f, 1.0f, 1.0f};
  constexpr std::array<float, 4> gray = {0.8f, 0.8f, 0.8f, 1.0f};
  constexpr std::array<float, 4> green = {0.0f, 1.0f, 0.0f, 1.0f};
  constexpr std::array<float, 4> blue = {0.0f, 0.0f, 1.0f, 1.0f};

  // glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red.data());
  glMaterialfv(GL_FRONT, GL_SPECULAR, white.data());
  glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);
  
  // Table top
  glPushMatrix();
  glScalef(5.0f, 0.2f, 5.0f);
  glTranslatef(0.0f, -0.5f, 0.0f);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray.data());
  Cube table_top = Cube();
  table_top.draw();
  glPopMatrix();

  // Left/back table foot
  glPushMatrix();
  glScalef(0.75f, 3.0f, 0.75f);
  glTranslatef(-2.25f, -0.5f, -2.25f);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray.data());
  Cube lb_table_ft = Cube();
  lb_table_ft.draw();
  glPopMatrix();

  // Left/front table foot
  glPushMatrix();
  glScalef(0.75f, 3.0f, 0.75f);
  glTranslatef(-2.25f, -0.5f, 2.25f);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray.data());
  Cube lf_table_ft = Cube();
  lf_table_ft.draw();
  glPopMatrix();

  // Right/back table foot
  glPushMatrix();
  glScalef(0.75f, 3.0f, 0.75f);
  glTranslatef(2.25f, -0.5f, -2.25f);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray.data());
  Cube rb_table_ft = Cube();
  rb_table_ft.draw();
  glPopMatrix();

  // Right/front table foot
  glPushMatrix();
  glScalef(0.75f, 3.0f, 0.75f);
  glTranslatef(2.25f, -0.5f, 2.25f);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray.data());
  Cube rf_table_ft = Cube();
  rf_table_ft.draw();
  glPopMatrix();

  // Red cube on top of the table
  glPushMatrix();
  glTranslatef(0.5f, 0.5f, -0.5f);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red.data());
  Cube red_cube = Cube();
  red_cube.draw();
  glPopMatrix();

  // Green sphere on top of the table
  glPushMatrix();
  glScalef(0.5f, 0.5f, 0.5f);
  glTranslatef(-1.5f, 1.0f, +1.0f);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green.data());
  Sphere green_sph = Sphere(128, 128);
  green_sph.draw();
  glPopMatrix();

  // Blue sphere on top of the table
  glPushMatrix();
  glScalef(0.5f, 0.5f, 0.5f);
  glTranslatef(2.5f, 1.0f, 1.0f);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue.data());
  Sphere blue_sph = Sphere(128, 128);
  blue_sph.draw();
  glPopMatrix();
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
  glutCreateWindow(cfg::title);

  auto myDispLambda = []() -> void {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setCamera();
    drawScene();
    glutSwapBuffers();  // update screen
    auto error = glGetError();
    if (error)
      printf("Error %d", error);
  };

  auto myKeyboardLambda = [](uint8_t key, int x, int y) -> void {
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
  };

  glutDisplayFunc(myDispLambda);
  glutKeyboardFunc(myKeyboardLambda);

  initialize();
  glutMainLoop();

  return 0;
}
