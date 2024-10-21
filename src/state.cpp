#include "state.hpp"
#include "callback.hpp"
#include "global.hpp"
#include <GLUT/glut.h>

static void set_home_callback();
static void set_stage_callback();

void change_state(State state)
{
    g_state = state;
    switch (state)
    {
    case STATE_HOME:
        set_home_callback();
        break;
    case STATE_STAGE:
        set_stage_callback();
        break;
    default:
        break;
    }
}

static void set_home_callback()
{
    glutDisplayFunc(display_home);
    glutKeyboardFunc(keyboard_home);
    glutMouseFunc(mouse_home);
    glutMotionFunc(motion_home);
    glutPassiveMotionFunc(motion_home);
}

static void set_stage_callback()
{
    glutDisplayFunc(display_stage);
    glutKeyboardFunc(keyboard_stage);
    glutMouseFunc(mouse_stage);
    glutMotionFunc(motion_stage);
    glutPassiveMotionFunc(motion_stage);
}