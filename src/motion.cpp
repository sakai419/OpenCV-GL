#include "callback.hpp"
#include "global.hpp"
#include <GLUT/glut.h>

void motion_home(int x, int y)
{
    const int easy = 400;
    const int normal = 500;
    const int hard = 600;
    if (y > easy - 50 && y < easy + 50)
    {
        g_difficulty = EASY;
    }
    else if (y > normal - 50 && y < normal + 50)
    {
        g_difficulty = NORMAL;
    }
    else if (y > hard - 50 && y < hard + 50)
    {
        g_difficulty = HARD;
    }
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