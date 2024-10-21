#include "state.hpp"
#include "callback.hpp"
#include "global.hpp"
#include <GLUT/glut.h>

void change_state(State state)
{
    g_state = state;
}

static void set_home_callback()
{
    glutDisplayFunc(display_home);
    glutKeyboardFunc(keyboard_home);
    glutMouseFunc(mouse_home);
    glutMotionFunc(motion_home);
    glutPassiveMotionFunc(motion_home);
}