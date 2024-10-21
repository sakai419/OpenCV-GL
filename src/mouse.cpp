#include "callback.hpp"
#include "global.hpp"
#include <GLUT/glut.h>

static void mouse_default(int button, int state, int x, int y);

void mouse_home(int button, int state, int x, int y)
{
    mouse_default(button, state, x, y);
}

void mouse_stage(int button, int state, int x, int y)
{
    mouse_default(button, state, x, y);
}

static void mouse_default(int button, int state, int x, int y)
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