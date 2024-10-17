#include "callback.hpp"
#include "global.hpp"
#include <GLUT/glut.h>

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            g_isLeftButtonOn = true;
        }
        else if (state == GLUT_UP)
        {
            g_isLeftButtonOn = false;
        }
    }
    else if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            g_isRightButtonOn = true;
        }
        else if (state == GLUT_UP)
        {
            g_isRightButtonOn = false;
        }
    }
}