#include "global.hpp"
#include "init.hpp"
#include "callback.hpp"
#include <GLUT/glut.h>

double g_angle1 = 0.0;
double g_angle2 = 0.0;
double g_distance = 5.0;
bool g_isLeftButtonOn = false;
bool g_isRightButtonOn = false;

void init_GL(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_X, WINDOW_Y);
    glutCreateWindow(WINDOWNAME);
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void set_callback_functions()
{
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(motion);
}