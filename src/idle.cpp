#include "global.hpp"
#include "callback.hpp"
#include "state.hpp"
#include <GLUT/glut.h>

void idle_home()
{
    glutPostRedisplay();
}

void idle_stage()
{
    if (time(NULL) - g_time > 5)
    {
        change_state(STATE_HOME);
    }
    glutPostRedisplay();
}