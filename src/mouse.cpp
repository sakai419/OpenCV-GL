#include "callback.hpp"
#include "global.hpp"
#include <GLUT/glut.h>

static void button_func(int button, int state);

void mouse_home(int button, int state, int x, int y)
{
    button_func(button, state);
}

void mouse_stage(int button, int state, int x, int y)
{
    button_func(button, state);
}

void mouse_answer(int button, int state, int x, int y)
{
    button_func(button, state);
}

void mouse_result(int button, int state, int x, int y)
{
    button_func(button, state);
}

static void button_func(int button, int state)
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