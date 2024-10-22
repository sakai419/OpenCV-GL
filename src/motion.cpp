#include "callback.hpp"
#include "global.hpp"
#include <GLUT/glut.h>

void motion_home(int x, int y)
{
    glutPostRedisplay();
}

void motion_stage(int x, int y)
{
    static int px = -1, py = -1;
    if (g_isLeftButtonOn == true)
    {
        if (px >= 0 && py >= 0)
        {
            g_angle1 += (double)-(x - px) / 20;
            g_angle2 += (double)(y - py) / 20;
        }
        px = x;
        py = y;
    }
    else if (g_isRightButtonOn == true)
    {
        if (px >= 0 && py >= 0)
        {
            g_distance += (double)(y - py) / 20;
        }
        px = x;
        py = y;
    }
    else
    {
        px = -1;
        py = -1;
    }
    glutPostRedisplay();
}

void motion_answer(int x, int y)
{
    glutPostRedisplay();
}

void motion_result(int x, int y)
{
    glutPostRedisplay();
}