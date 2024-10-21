#include "global.hpp"
#include "callback.hpp"
#include "state.hpp"
#include <GLUT/glut.h>

using namespace std::chrono;

void idle_home()
{
    glutPostRedisplay();
}

void idle_stage()
{
    auto now = high_resolution_clock::now();
    auto elapsed = duration<double>(now - g_time).count();
    remaining_time = 5.0 - elapsed;

    if (remaining_time < 0.0)
    {
        change_state(STATE_HOME);
    }
    glutPostRedisplay();
}