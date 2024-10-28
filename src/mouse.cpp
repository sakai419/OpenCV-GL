#include "callback.hpp"
#include "global.hpp"
#include "state.hpp"
#include <GLUT/glut.h>

static void button_func(int button, int state);

void mouse_home(int button, int state, int x, int y)
{
    const int difficulties[2] = {400, 600};

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (y > difficulties[0] - 50 && y < difficulties[1] + 50)
        {
            change_state(STATE_STAGE);
        }
    }
}

void mouse_stage(int button, int state, int x, int y)
{
    button_func(button, state);
}

void mouse_answer(int button, int state, int x, int y)
{
    const int x1 = 310, x2 = 500, x3 = 690;
    const int y1 = 270, y2 = 430, y3 = 590;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (x > x1 - 95 && x < x3 + 95 && y > y1 - 80 && y < y2 + 80)
        {
            change_state(STATE_RESULT);
        }
    }
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